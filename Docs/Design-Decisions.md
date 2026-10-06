

1. Top-Level Folder Structure (Unreal Engine 5)

For a three-person team, a strict folder structure prevents Git merge conflicts and lost assets. All active development files will live inside the standard UE5 Content folder.

    Content/

        Core/: Contains foundational files like the GameMode, PlayerController, and base Player Character.

        Blueprints/

            Components/: Houses all modular Actor Components (e.g., Interaction, Pressure, Memory Echo).

            Interactables/: Contains specific objects the player interacts with (e.g., BP_FamilyPhoto, BP_HospitalBracelet).

            Puzzles/: Contains logic for the Sentence Reconstruction puzzles and environmental puzzle managers.

        Data/: Stores Data Assets and Data Tables used for driving narrative text and puzzle parameters.

        UI/: Widget Blueprints for the main menu, HUD, and inspection screens.

        Levels/: Contains the master maps for the five main levels, organized by emotional stage (e.g., Level 1 - Confusion/Denial through Level 5 - Truth/Acceptance).

        Audio/: Sound cues, voiceover lines, and ambient tracks.

        Art/: 3D meshes, materials, textures, and VFX.

2. Hybrid Class Hierarchy (C++ & Blueprints)

To balance performance with rapid iteration, foundational classes are built in C++ and extended into Blueprints for visual scripting and asset assignment.
Core Framework Classes

    AWWNS_GameMode (C++) ➔ BP_WWNS_GameMode (Blueprint): Manages global game rules, level transitions, and tracking which of the five levels the player is currently in.

    AWWNS_PlayerController (C++) ➔ BP_PlayerController: Handles UI inputs, pausing, and camera control switching (e.g., switching from locomotion to an object inspection screen).

    AWWNS_PlayerCharacter (C++) ➔ BP_PlayerCharacter: The main protagonist class. Contains basic movement logic, camera setup, and serves as the host for modular Actor Components.

Modular Actor Components

These are attached to the BP_PlayerCharacter or environmental objects to handle specific mechanics without bloating the main classes.

    UInteractionComponent (C++): Attached to the player. Fires raycasts from the camera to detect objects in the environment.

    UEmotionalPressureComponent (C++ / Blueprint): Attached to the player. Tracks the psychological stress scale from 0% (Calm) to 100% (Collapse/Death). Contains functions like AddPressure() and ReducePressure().

    UMemoryEchoComponent (Blueprint): Attached to environmental objects. Listens for interaction events to trigger audio, visual fragments, or dialogue.

3. Blueprint Interfaces

Interfaces allow different classes to communicate without creating hard memory references.

    BPI_Interactable

        Interact(): Executed when the player clicks on the object.

        OnInspect(): Executed when the object is picked up for closer 3D examination.

        OnHover() / OnUnhover(): Executed when the player's crosshair passes over the object to trigger UI outlines or prompts.

    BPI_PuzzleElement

        OnPuzzleAction(): Triggered when a puzzle step is taken.

        OnPuzzleFailed(): Triggers environmental reactions, such as the living room temporarily becoming dark and distorted.

        OnPuzzleSolved(): Triggers positive progression or flashback sequences.

4. Data-Driven Narrative & Puzzle Architecture

Instead of hardcoding text or logic into the maps, use Data Assets to make balancing and writing easy for the team.

    DA_SentencePuzzle (Data Asset Class):

        Variables: Array<String> Fragments (e.g., "I", "didn't", "mean", "to", "hurt", "you").

        Variables: Array<String> CorrectSequence.

        Variables: SoundCue MemoryEchoTrigger (plays when solved).

    DA_MemoryEcho (Data Asset Class):

        Variables: SoundCue DialogueLine.

        Variables: NiagaraSystem VisualDistortion.

        Variables: Float PressureAdjustment (determines how much this memory reduces or increases the player's emotional pressure).

5. Interaction Flow Example

    The player looks at the Hospital Bracelet.

    The UInteractionComponent on the player detects the object and calls OnHover() via BPI_Interactable.

    The player clicks. The UInteractionComponent calls Interact().

    The BP_HospitalBracelet receives the Interact() interface message.

    The attached UMemoryEchoComponent reads its assigned DA_MemoryEcho file and plays the associated narrative audio.