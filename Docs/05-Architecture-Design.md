# Technical Architecture — Words We Never Said

## 1. Core Development Philosophy

**Words We Never Said** uses a hybrid **C++ + Blueprint** architecture.

- **C++** is used for stable foundational systems, reusable base classes, interfaces, and complex or performance-sensitive logic.
- **Blueprints** are used for visual scripting, asset configuration, level-specific logic, puzzle implementation, and rapid iteration.
- Gameplay systems are designed to be modular to reduce coupling and Git merge conflicts.
- The Player Character remains lightweight and hosts reusable Actor Components.
- Gameplay state is separated from presentation systems such as audio, VFX, lighting, UI, and cinematics.

### Architectural Principles

1. Single Responsibility
2. Modularity
3. Low Coupling
4. Reusability
5. Data-Driven Design
6. Event-Based Communication
7. Separation of Gameplay and Presentation
8. Lightweight Player Character

---

## 2. High-Level Architecture

```text
GameInstance
    │
    ├── Persistent Story State
    ├── Save/Load Coordination
    └── Global Progression
            │
            ▼
GameMode
    │
    └── Current Level Rules / Initialization
            │
            ▼
PlayerController
    │
    ├── Input
    ├── UI Routing
    └── Camera State
            │
            ▼
PlayerCharacter
    │
    ├── Interaction Component
    ├── Emotional Pressure Component
    └── Other Modular Components
            │
            ├───────────────┐
            ▼               ▼
    Interaction System   Pressure System
            │               │
            ▼               ▼
      Interactables    Memory / Story Events
            │               │
            └───────┬───────┘
                    ▼
          Presentation Systems
       Audio / VFX / UI / Lighting
              / Cinematics
```

---

## 3. Unreal Gameplay Framework

The main Unreal gameplay classes are:

```text
AWWNS_GameInstance
AWWNS_GameMode
AWWNS_PlayerController
AWWNS_PlayerCharacter
AWWNS_Interactable
```

The naming prefix `AWWNS_` refers to **Words We Never Said**.

---

## 4. Game Instance

### Class

```text
AWWNS_GameInstance
```

### Responsibility

`AWWNS_GameInstance` manages persistent game state that must survive level transitions.

You can break your GameInstance responsibilities into three lightweight Subsystems:

UStoryProgressionSubsystem:

Responsibility: Tracks which of the 5 levels the player is on, which narrative flags are checked, and which DA_StoryEvent conditions have been met.

UMemoryTrackingSubsystem:

Responsibility: Keeps an array of which DA_MemoryEcho files the player has discovered.

USaveCoordinationSubsystem:

Responsibility: Only handles writing/reading the local .sav files to the hard drive, asking the other two subsystems for their data when it's time to save.


GameInstance
    │
    ├── UStoryProgressionSubsystem (Manages story flags & current level)
    ├── UMemoryTrackingSubsystem (Manages discovered echoes & puzzles)
    └── USaveCoordinationSubsystem (Handles disk read/writes)

### Important Rule

`GameInstance` should contain **persistent game state**, not level-specific gameplay rules.

---

## 5. Game Mode

### Class

```text
AWWNS_GameMode
```

### Responsibility

`GameMode` handles rules and initialization for the **current level**.

Examples:

- Level initialization
- Player spawning
- Current-level rules
- Level-specific setup
- Starting conditions

### Important Rule

`GameMode` should **not** be responsible for persistent story progression.

Persistent progression belongs to `AWWNS_GameInstance`.

---

## 6. Player Controller

### Class

```text
AWWNS_PlayerController
```

### Responsibilities

- Player input
- UI routing
- Camera state
- Input mode switching
- First-person exploration state
- Fixed-camera or inspection state
- Interaction input forwarding

The Player Controller should not contain puzzle-specific logic.

---

## 7. Player Character

### Class

```text
AWWNS_PlayerCharacter
```

### Responsibilities

- Player movement
- Character representation
- Basic locomotion
- Hosting modular components
- Connecting player actions to gameplay systems

The Player Character should remain lightweight.

Puzzle logic, memory logic, pressure logic, and other systems should be implemented through dedicated components or external systems rather than continuously expanding the Player Character.

---

## 8. Interactable Base Class

### Class

```text
AWWNS_Interactable
```

Not every object in the world needs to inherit from this class.

Normal environment meshes do not need interaction functionality.

Potential hierarchy:

```text
AWWNS_Interactable
├── BP_InspectableObject
├── BP_PickupObject
├── BP_Door
├── BP_PuzzleObject
└── BP_EmotionalObject
```

Blueprint Interfaces can also allow objects to participate in the interaction system without requiring a rigid inheritance hierarchy.

---

## 9. Interaction System

### Component

```text
UInteractionComponent
```

The Interaction Component is attached to the Player Character.

### Responsibilities

- Detect interactable objects
- Perform camera-aligned traces
- Determine what the player is looking at
- Handle interaction input
- Route interaction requests
- Support inspection
- Support pickup/drop interactions

### Trace

A dedicated Unreal collision trace channel should be created:

```text
Interactable
```

The component uses this channel to detect objects that can be interacted with.

The interaction system should avoid unnecessary continuous polling and instead use controlled tracing based on player state and input.

---

## 10. Interaction Interface

### Blueprint Interface

```text
BPI_Interactable
```

### Functions

```text
CanInteract()
OnHover()
OnUnhover()
Interact()
OnInspect()
```

This keeps the interaction system loosely coupled.

Different objects can implement the interface differently without the Player Character needing to know their concrete classes.

---

## 11. Inspection System

Inspection is treated as a modular interaction state.

When the player examines an object:

```text
Player looks at object
        ↓
Interaction Component detects object
        ↓
CanInteract()
        ↓
OnInspect()
        ↓
Inspection state
        ↓
Object-specific response
```

Possible responses include:

- Description
- Dialogue
- Memory Echo
- Camera movement
- Audio
- VFX
- Pressure change
- Story event

---

## 12. Emotional Pressure System

### Component

```text
UEmotionalPressureComponent
```

The component maintains the player's current emotional pressure.

Conceptual range:

```text
0 ───────────────────────────── 100
Calm                         Critical
```

### Main Functions

```text
AddPressure(float Amount)
ReducePressure(float Amount)
GetCurrentPressure()
```

### Pressure Stages

```text
Calm
Uneasy
Distressed
Critical
Collapse
```

The exact numeric thresholds can be configured later.

---

## 13. Pressure Events

The Pressure Component exposes events rather than forcing other systems to constantly check its value.

Important events include:

```text
OnPressureChanged
OnPressureThresholdReached
OnPressureCritical
```

Other systems can subscribe to these events.

For example:

```text
Pressure increases
        ↓
Threshold reached
        ↓
Environment reacts
        ↓
Lighting changes
Audio distortion increases
VFX appear
UI reacts
```

At critical pressure, the game may trigger a collapse/death state depending on the current level.

---

## 14. Memory Echo System

### Component

```text
UMemoryEchoComponent
```

A Memory Echo Component can be attached to interactable objects or other trigger actors.

Its responsibility is to detect and initiate a memory event.

It should **not** directly own every downstream presentation effect.

### Flow

```text
Memory Echo
     ↓
Memory Triggered
     ↓
Audio / VFX / UI / Pressure / Story
```

This keeps the Memory Echo system reusable.

---

## 15. Memory Data Asset

### Data Asset

```text
DA_MemoryEcho
```

Example fields:

```text
EchoAudio
EchoVFX
PressureDelta
SubtitleText
```

Additional fields can be added later if required.

The Data Asset allows different memory echoes to be configured without creating unique C++ classes.

---

## 16. Puzzle System

Puzzle logic should be modular and reusable.

Puzzle-specific objects can use:

```text
BPI_PuzzleElement
```

or dedicated Blueprint puzzle actors.

Puzzle success can trigger:

- Story progression
- Memory Echoes
- Flashbacks
- Environmental changes
- New interactions
- Level progression

Puzzle failure can trigger:

- Environmental distortion
- Dialogue fragments
- Memory fragments
- Pressure changes
- Temporary state changes

---

## 17. Puzzle Interface

### Blueprint Interface

```text
BPI_PuzzleElement
```

### Functions

```text
OnPuzzleAction()
OnPuzzleFailed()
OnPuzzleSolved()
```

This allows different puzzle objects to communicate with puzzle controllers without strong dependencies.

---

## 18. Sentence Reconstruction System

One of the game's puzzle mechanics is sentence reconstruction.

The player receives predefined word fragments and must arrange them into the correct sentence.

Example:

```text
I / didn't / mean / to / hurt / you
```

The system checks the player's sequence against the correct sequence.

### Possible Flow

```text
Player selects fragments
        ↓
Fragments are arranged
        ↓
Puzzle checks sequence
        ↓
Correct?
   ┌────┴────┐
   │         │
  Yes        No
   │         │
Solved     Failed
   │         │
   ▼         ▼
Story      Memory /
Event      Distortion
```

---

## 19. Sentence Puzzle Data Asset

### Data Asset

```text
DA_SentencePuzzle
```

Example fields:

```text
AvailableFragments
CorrectSequence
OnSolvedEcho
```

The same puzzle system can therefore support different sentence puzzles across the five levels.

---

## 20. Story Event System

The game uses story events to connect gameplay actions to narrative progression.

### Data Asset

```text
DA_StoryEvent
```

Example fields:

```text
StoryID
RequiredConditions
TriggeredEvents
UnlockedContent
```

Possible conditions include:

- Puzzle completed
- Memory discovered
- Object inspected
- Story flag active
- Level completed
- Required perspective unlocked

Possible triggered events include:

- Unlocking a memory
- Changing the environment
- Starting dialogue
- Activating a cinematic
- Unlocking a door
- Updating story progression

---

## 21. Save System

The save system stores persistent progression.

Potential save data includes:

```text
Current Level
Story Flags
Completed Puzzles
Discovered Memories
Important Decisions
Unlocked Content
```

Save/load coordination is handled through the persistent game-state architecture.

`AWWNS_GameInstance` coordinates with the save system, while actual save data should be stored using Unreal's SaveGame system.

---

## 22. Level Architecture

The game contains five main levels:

```text
L_01_ConfusionDenial
L_02_ReconstructingPast
L_03_FathersWeight
L_04_ThreePerspectives
L_05_TruthAndAcceptance
```

Each level should primarily contain:

- Level-specific environment
- Level-specific puzzle actors
- Level-specific triggers
- Level-specific story events
- Level-specific lighting
- Level-specific audio
- Level-specific cinematics

Reusable systems should remain outside individual level logic.

---

## 23. Level Transitions

Normal level progression should use the simplest Unreal loading approach that satisfies the project requirements.

Example:

```text
Level 1 Complete
      ↓
Save Progress
      ↓
Update GameInstance
      ↓
Load Level 2
      ↓
Initialize Level 2 GameMode
```

Within-level environmental changes should not automatically require separate streamed levels.

For example, Level 4's three perspectives can be implemented as states or environment transformations within the same level unless technical requirements later justify streaming.

---

## 24. Presentation Systems

Presentation systems respond to gameplay events.

These include:

- Audio
- VFX
- Lighting
- Post Processing
- UI
- Cinematics
- Camera effects

Gameplay systems own the state.

Presentation systems own how that state is shown to the player.

Example:

```text
Pressure reaches Critical
        ↓
Gameplay event
        ↓
Presentation systems respond
        ├── Audio distortion
        ├── Post-process effect
        ├── Lighting change
        ├── VFX
        └── UI feedback
```

---

## 25. Audio Organization

```text
Content/Audio/
├── Ambient/
├── Dialogue/
├── SFX/
└── Music/
```

### Ambient

Environmental sounds such as:

- Hospital ambience
- Room tone
- Wind
- Electrical hum
- Distant environmental sounds

### Dialogue

- Character dialogue
- Memory dialogue
- Voice fragments
- Story narration

### SFX

- Doors
- Objects
- Footsteps
- Interaction sounds
- Puzzle feedback

### Music

- Level themes
- Emotional themes
- Tension
- Ending music

---

## 26. Cinematics

Cinematics are organized separately from gameplay logic.

```text
Content/Cinematics/
├── Sequences/
├── Cameras/
└── Animations/
```

Gameplay systems should trigger cinematics rather than embedding cinematic logic directly inside unrelated gameplay classes.

---

## 27. Project Folder Structure

```text
Graduation_Project/
├── Config/
│
├── Content/
│   ├── Art/
│   │   ├── Environment/
│   │   ├── Meshes/
│   │   ├── Materials/
│   │   ├── Textures/
│   │   ├── Props/
│   │   ├── Characters/
│   │   └── VFX/
│   │
│   ├── Audio/
│   │   ├── Ambient/
│   │   ├── Dialogue/
│   │   ├── SFX/
│   │   └── Music/
│   │
│   ├── Blueprints/
│   │   ├── Characters/
│   │   ├── Components/
│   │   ├── Interactables/
│   │   ├── Interfaces/
│   │   ├── Puzzles/
│   │   ├── Memory/
│   │   ├── Emotional/
│   │   └── Triggers/
│   │
│   ├── Cinematics/
│   │   ├── Sequences/
│   │   ├── Cameras/
│   │   └── Animations/
│   │
│   ├── Core/
│   │   ├── Game/
│   │   ├── Player/
│   │   ├── Save/
│   │   └── Systems/
│   │
│   ├── Data/
│   │   ├── Memories/
│   │   ├── Puzzles/
│   │   ├── Dialogue/
│   │   ├── EmotionalObjects/
│   │   ├── Story/
│   │   └── Levels/
│   │
│   ├── Developer/
│   │   ├── Debug/
│   │   └── Test/
│   │
│   ├── Levels/
│   │   ├── L_01_ConfusionDenial/
│   │   ├── L_02_ReconstructingPast/
│   │   ├── L_03_FathersWeight/
│   │   ├── L_04_ThreePerspectives/
│   │   └── L_05_TruthAndAcceptance/
│   │
│   ├── UI/
│   │   ├── HUD/
│   │   ├── Menus/
│   │   ├── Dialogue/
│   │   ├── Puzzles/
│   │   └── Subtitles/
│   │
│   └── Animations/
│       ├── Characters/
│       └── Props/
│
├── Source/
│   └── Graduation_Project/
│       ├── Core/
│       ├── Player/
│       ├── Interaction/
│       ├── Memory/
│       ├── Puzzle/
│       ├── Pressure/
│       └── Save/
│
├── Docs/
│
├── Graduation_Project.uproject
└── README.md
```

---

## 28. C++ vs Blueprint Responsibilities

### C++ Responsibilities

Use C++ for:

- Core gameplay framework classes
- GameInstance
- GameMode
- PlayerController
- PlayerCharacter base class
- Reusable Actor Components
- Interaction tracing
- Pressure calculations
- Interfaces
- Reusable puzzle foundations
- Save system foundations
- Complex calculations

### Blueprint Responsibilities

Use Blueprints for:

- Asset assignment
- Level-specific logic
- Individual interactable behavior
- Puzzle setup
- Memory Echo configuration
- Story event configuration
- Audio/VFX triggering
- Cinematic triggering
- UI behavior
- Rapid iteration

### General Rule

If logic is highly reusable and foundational, prefer C++.

If logic is content-specific and likely to change during level design, prefer Blueprint.

---

## 29. Communication Between Systems

Systems should communicate through:

- Interfaces
- Events
- Delegates
- Data Assets
- GameInstance state
- Controlled references

Avoid unnecessary direct dependencies.

Example:

```text
Puzzle Solved
      ↓
Puzzle Event
      ↓
Story System
      ↓
Memory Unlocked
      ↓
Memory Event
      ↓
Audio / VFX / UI / Pressure
```

This is preferable to having the puzzle directly manipulate every presentation system.

---

## 30. Git and Collaboration Considerations

The project is developed by three team members.

The architecture should minimize conflicts through modularization and clear ownership.

### Important Practices

- Use feature branches.
- Use pull requests for major changes.
- Avoid having multiple people edit the same Blueprint simultaneously when possible.
- Keep systems modular.
- Establish ownership of major systems.
- Integrate changes regularly.
- Communicate before modifying shared core assets.
- Keep reusable logic separate from level-specific content.

### Important Clarification

Interfaces do not prevent Git conflicts or memory corruption.

They reduce coupling between systems, which can make collaboration and maintenance easier.

Git conflicts are managed through:

- Branching
- Pull requests
- Clear ownership
- Regular integration
- Modular files
- Team communication

---

## 31. Architectural Principles

### Single Responsibility

Each class or component should have one primary responsibility.

### Modularity

Systems should be divided into reusable components.

### Low Coupling

Systems should avoid unnecessary direct dependencies.

### Reusability

Common behavior should be reusable across levels.

### Data-Driven Design

Data Assets should control configurable content such as:

- Memories
- Puzzles
- Story events
- Dialogue
- Emotional objects

### Event-Based Communication

Systems should communicate through events where appropriate instead of tightly coupling gameplay and presentation.

### Separation of Gameplay and Presentation

Gameplay determines what happens.

Presentation determines how it looks and sounds.

### Lightweight Player Character

The Player Character should host systems rather than becoming the location for all game logic.

---

## 32. Example Complete Gameplay Flow

Example: The player inspects an important emotional object.

```text
Player looks at object
        ↓
UInteractionComponent
        ↓
Interactable trace
        ↓
BPI_Interactable::CanInteract()
        ↓
BPI_Interactable::OnInspect()
        ↓
UMemoryEchoComponent
        ↓
Memory Echo triggered
        ↓
DA_MemoryEcho loaded
        ↓
Memory event
        ├── Audio
        ├── VFX
        ├── Subtitle
        ├── Pressure Change
        └── Story Event
                ↓
        Story progression updated
                ↓
        AWWNS_GameInstance
```

---

## 33. Architecture Summary

The architecture of **Words We Never Said** is built around a modular hybrid C++/Blueprint approach.

The key structure is:

```text
Persistent State
    ↓
GameInstance
    ↓
Level Rules
    ↓
GameMode
    ↓
Player Controller
    ↓
Player Character
    ↓
Modular Components
    ├── Interaction
    ├── Emotional Pressure
    └── Memory Echo
            ↓
     Gameplay Events
            ↓
     Story / Puzzle Systems
            ↓
      Presentation
   Audio / VFX / UI /
 Lighting / Cinematics
```

This architecture provides:

- Clear separation of responsibilities
- Reusable gameplay systems
- Data-driven content
- Flexible Blueprint iteration
- Stable C++ foundations
- Lower coupling between systems
- Better collaboration for a three-person team
- Easier expansion across the five game levels
