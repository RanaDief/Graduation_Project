<!-- Page 1 -->


# WORDS WE NEVER SAID  


# GAME DESIGN DOCUMENT  


Version 1.0 — Initial Production Blueprint  Graduation Project | Semester 1, 2026/2027  Team: Rana Dief, Mahmoud Amr, Osama Alashri  Engine: Unreal Engine

---

<!-- Page 2 -->


## Document Control  



<table><tr><td>Field</td><td>Details</td></tr><tr><td>Project</td><td>Words We Never Said (proposal title: Psychological Puzzle Game)</td></tr><tr><td>Purpose</td><td>Define the game&#x27;s experience, narrative, mechanics, content boundaries, implementation needs, and acceptance criteria.</td></tr><tr><td>Version / status</td><td>Version 1.0 initial GDD</td></tr><tr><td>Source of truth</td><td>Final Graduation Project Proposal supplied by the team.</td></tr><tr><td>Important note</td><td>Three levels are confirmed by the proposal. The exact names and complete content of each level remain provisional until approved by the team.</td></tr></table>  


## How to Use This GDD  


How to Use This GDDUse this document as the shared reference for design and implementation. Update it when a decision changes, and record significant changes in the change log. Do not add features that threaten completion of the three- level game without team agreement.  


## Contents  


Contents1. 1. Game Overview2. 2. Vision and Design Pillars3. 3. Target Experience4. 4. Narrative Overview5. 5. Gameplay Loop and Controls6. 6. Core Gameplay Systems7. 7. Level Structure8. 8. Art Direction9. 9. Audio Direction10. 10. UI and Accessibility11. 11. Technical Design12. 12. Content and Assets13. 13. Team Workflow14. 14. Testing and Acceptance Criteria15. 15. Risks and Scope Control16. 16. Milestones17. 17. Open Decisions18. Appendix A. Level Design Template  


Words We Never Said (proposal title: Psychological Puzzle Game)  


Define the game's experience, narrative, mechanics, content boundaries, implementation needs, and acceptance criteria.  


Version 1.0 initial GDD  


Final Graduation Project Proposal supplied by the team.  


Three levels are confirmed by the proposal. The exact names and complete content of each level remain provisional untill approved by the team.

---

<!-- Page 3 -->


## 1. Game Overview  



<table><tr><td>Category</td><td>Definition</td></tr><tr><td>Title</td><td>Words We Never Said</td></tr><tr><td>Genre</td><td>3D psychological puzzle-adventure</td></tr><tr><td>Mode / camera</td><td>Single-player; first-person</td></tr><tr><td>Engine</td><td>Unreal Engine</td></tr><tr><td>Core experience</td><td>Explore distorted environments, inspect and place symbolic objects, solve environmental puzzles, reconstruct memories, and discover different perspectives on a family conflict.</td></tr><tr><td>Themes</td><td>Family conflict, guilt, misunderstanding, empathy, communication, forgiveness, and acceptance.</td></tr><tr><td>Combat</td><td>None.</td></tr><tr><td>Content scope</td><td>Three interconnected levels forming a complete beginning-to-ending experience.</td></tr><tr><td>Performance target</td><td>At least 30 FPS on the team&#x27;s designated development hardware, as stated in the proposal.</td></tr></table>  


### 1.1 High Concept  


A teenage boy lies in a coma after a car accident that follows a painful argument with his father. Inside his subconscious, the hospital and related environments become distorted spaces shaped by fragmented memories and unresolved emotions. The player explores these spaces, solves symbolic puzzles, reconstructs the events surrounding the accident, and works toward understanding the family conflict.  


### 1.2 Player Promise  


The player will not simply be told what happened. They discover the story by examining spaces, connecting objects, solving puzzles, and noticing how the environment changes with the protagonist's emotional state.  


### 1.3 Scope Boundaries  


- IN SCOPE: three connected levels, first-person exploration; object inspection, interaction, and placement; symbolic environmental puzzles; sentence reconstruction; memory reconstruction; environmental changes linked to emotional pressure; ambient audio and limited dialogue; functional testing and playtesting.- OUT OF SCOPE: extra levels; combat, weapons, enemies, and advanced AI opponents; procedural puzzles; extensive branching narratives; multiplayer; clinical or therapeutic claims; extensive cinematic cutscenes; professional full voice acting; VR, mobile, and console ports.  


## 2. Vision and Design Pillars  



<table><tr><td>Pillar</td><td>Rule</td><td>Application</td></tr></table>

---

<!-- Page 4 -->



<table><tr><td>Environmental storytelling first</td><td>Important information should be discoverable in spaces and objects, not only dialogue.</td><td>Room arrangement, object placement, lighting, sound, and visual distortion carry story information.</td></tr><tr><td>Psychological, not horror</td><td>Create emotional unease without conventional horror threats.</td><td>Unnatural proportions, quiet sound, familiar spaces behaving incorrectly, restrained distortion.</td></tr><tr><td>Puzzles have narrative meaning</td><td>Major puzzles should reveal or reframe information about the family conflict.</td><td>Objects and reconstructed phrases connect to memories and relationships.</td></tr><tr><td>Readable progression</td><td>Players should understand what is interactive and why progress is blocked.</td><td>Consistent prompts, clear puzzle states, contextual clues, reversible mistakes.</td></tr><tr><td>Feasible scope</td><td>A complete, polished experience matters more than feature count.</td><td>Reusable systems and assets; no unapproved expansion.</td></tr></table>  


### 2.1 Non-Goals  


- The game is not a clinical simulation and does not diagnose or treat mental-health conditions.- The pressure system is a gameplay representation of stress, not a scientifically validated emotion model.- The game is not a combat game, open world, or traditional survival-horror experience.  


## 3. Target Experience and Audience  


The intended audience is players who enjoy story- driven exploration, environmental puzzles, symbolic imagery, and emotionally focused single- player games. The intended experience is reflective and investigative rather than fast- paced.  


### 3.1 Desired Player Emotions  


- Curiosity about the distorted hospital and memories.- Confusion that gradually becomes understanding.- Tension when emotional pressure rises.- Empathy as different family perspectives are revealed.- Emotional resolution at the ending.  


### 3.2 Success Signals  


- All three levels can be completed without progression-blocking bugs.- At least 10 people participate in playtesting.- At least \(80\%\) of playtesters identify the key events leading to the accident and understand the conflict from different perspectives.- Target at least 30 FPS on designated development hardware.- Players understand core interactions and puzzle feedback.

---

<!-- Page 5 -->


## 4. Narrative Overview  


## 4.1 Premise  


After a painful argument with his father, a teenage boy leaves home emotionally overwhelmed and is involved in a car accident. He falls into a coma. The player knows from the beginning that the protagonist is in a coma and is trying to wake up. His subconscious creates a distorted hospital- like world where objects, rooms, and fragmented memories reflect unresolved feelings.  


## 4.2 Narrative Goals  


4.2 Narrative Goals- Let players reconstruct the evening and events connected to the accident.- Show that the argument can be understood differently by the son, father, and mother.- Use the environment and puzzles to communicate guilt, pressure, misunderstanding, and care.- Build toward acceptance and a clearer understanding of the family relationship.- Avoid presenting any character as a simple villain; communicate motivations through evidence and perspective.  


## 4.3 Narrative Delivery  



<table><tr><td>Method</td><td>Purpose</td><td>Guidance</td></tr><tr><td>Environmental storytelling</td><td>Communicate context without stopping play.</td><td>Use layout, objects, lighting, and changes in familiar spaces.</td></tr><tr><td>Memory fragments</td><td>Reveal part of an event over time.</td><td>Keep fragments short, purposeful, and connected to an interaction or puzzle.</td></tr><tr><td>Symbolic objects</td><td>Give abstract emotions a concrete form.</td><td>Each major object should have a clear narrative association and preferably a gameplay function.</td></tr><tr><td>Perspective sequences</td><td>Show different interpretations of the same event.</td><td>Reuse an event/location while changing contextual cues and what the player can infer.</td></tr><tr><td>Limited dialogue/audio</td><td>Clarify essential information and add emotional texture.</td><td>Use sparingly; avoid long, unskippable exposition.</td></tr></table>  


## 4.4 Narrative Guardrails  


4.4 Narrative Guardrails- The coma premise should be clear early; the mystery is what happened and how the family understood it.- Distorted perceptions are not necessarily objective facts about the family.- Effects should support comprehension, not obscure every clue.- The ending must be consistent with established information.  


## 5. Gameplay Loop and Controls  


## 5.1 Core Gameplay Loop  


5.1 Core Gameplay Loop19. Enter and orient within a contained environment.20. Observe the room and identify notable objects, symbols, and inconsistencies.21. Inspect relevant objects to gather clues.

---

<!-- Page 6 -->


22. Connect clues, place objects, or reconstruct a phrase to solve the puzzle.  
23. Trigger a memory fragment or environmental change that reveals information.  
24. Move to the next area or level with a clearer understanding of the story.  


### 5.2 Interaction Feedback  


- Show a consistent prompt when an object is interactable.- Give visual feedback when an object is selected, carried, or placed.- Communicate correct and incorrect puzzle states clearly.- Keep interaction range and targeting consistent across levels.- Allow players to cancel or exit an interaction.  


## 6. Core Gameplay Systems  


### 6.1 Exploration and Environmental Interaction  


- Required: first-person movement, camera look, interaction targeting, inspectable objects, and basic feedback.- Each level sheet must list its critical interactables.- Decorative props must not be confused with essential puzzle objects without a differentiating cue.- Distortion must not make routes unfair or navigation impossible.  


### 6.2 Object Inspection, Carrying, and Placement  


- Inspection may reveal a short description, visual detail, sound, or clue.- Only puzzle-critical objects need carrying or placement behavior.- Objects should snap to valid sides and visibly communicate acceptance.- Required objects must not be permanently lost or placed into invalid states.- Prefer reusable interaction components over bespoke logic for every prop.  


### 6.3 Symbolic Puzzle System  


Puzzles turn story clues into actions. The proposal includes symbolic objects and sentence reconstruction. Puzzles are authored and deterministic, not procedurally generated.  


- Every puzzle defines narrative purpose, goal, clues, valid solution, feedback, completion trigger, and recovery behavior.- Sentence reconstruction uses predefined word pieces assembled into a target sentence.- Solutions should be discoverable from environmental clues or memory fragments.- Avoid puzzles requiring unstable outside knowledge.- Wrong answers should provide feedback or a reversible state, not permanently block progress.  


### 6.4 Memory Reconstruction  


- A solved puzzle or key interaction may reveal a short audiovisual fragment, alter the room, or unlock a new interpretation.- Each fragment should answer a narrative question, provide evidence, or reframe an earlier event.- Combine fragments with a changed object, room state, or newly accessible path where possible.- Track triggered fragments to prevent unintended repetition.- Make fragments skippable or replayable where practical.

---

<!-- Page 7 -->


## 6.5 Emotional Pressure System  


The pressure system links the protagonist's psychological state to environmental effects and creates manageable tension. The proposal requires environmental effects that change according to stress.  



<table><tr><td>Element</td><td>Initial proposal</td></tr><tr><td>Pressure value</td><td>A bounded internal value, e.g. 0–100; thresholds require tuning.</td></tr><tr><td>Increase triggers</td><td>Authored story events, selected puzzle mistakes, or designated distressing cues.</td></tr><tr><td>Decrease triggers</td><td>Safe/restorative areas, resolving a key interaction, or completing a calming objective.</td></tr><tr><td>Environmental response</td><td>Lighting shifts, sound distortion, visual instability, or altered room details; keep clues legible.</td></tr><tr><td>Critical state</td><td>Clearly signaled. If high pressure causes a reset/death, provide warning and a fair checkpoint/recovery path.</td></tr><tr><td>Feedback</td><td>Consistent audiovisual cues communicate escalation.</td></tr><tr><td>Balancing</td><td>Pressure should support the story, not make puzzle solving unfair.</td></tr></table>  


Open design decision: the proposal does not fully specify whether maximum pressure causes a reset/death or only environmental escalation. Prototype environmental escalation first, then approve any failure consequence.  


### 6.6 Audio-Visual State Changes  


- Use a small reusable set of effects: light flicker, material/color shift, sound filtering, room variation, and brief distortion.- Define consistent normal, elevated, and critical pressure states.- Avoid effects that hide puzzle-critical information or cause motion discomfort.- Sound reinforces spatial and narrative information; it does not replace essential visual clues.  


## 7. Level Structure  


The proposal confirms three interconnected levels but does not specify their final names or complete level- by- level content. The following is a provisional structure based on the established story premise. Confirm or replace these names and beats before production is locked.  



<table><tr><td>Level</td><td>Provisional role</td><td>Primary activity</td><td>Narrative outcome</td></tr><tr><td>1 – The Hospital That Feels Wrong</td><td>Introduction and orientation</td><td>Explore a distorted hospital room, inspect key objects, learn interaction rules, solve an introductory puzzle.</td><td>Understand the coma premise and the goal of waking up.</td></tr><tr><td>2 – The Family Memory</td><td>Conflict reconstruction and perspective</td><td>Explore a memory-based family environment, connect clues, reconstruct parts of</td><td>Understand the context of the argument and reconsider assumptions.</td></tr></table>

---

<!-- Page 8 -->



<table><tr><td></td><td></td><td>the argument, encounter<br>evidence of differing<br>perspectives.</td><td></td></tr><tr><td>3 - The Crash and<br>Acceptance</td><td>Climax and resolution</td><td>Reconstruct<br>accident-related memories,<br>solve a final symbolic<br>puzzle, connect earlier<br>evidence.</td><td>Clarify key events, resolve<br>the central<br>misunderstanding, reach the<br>intended ending.</td></tr></table>


7.1 Level 1 - The Hospital That Feels Wrong (Provisional)



<table><tr><td>Field</td><td>Initial plan</td></tr><tr><td>Purpose</td><td>Teach movement, inspection, interaction, and basic puzzle logic while establishing the coma premise.</td></tr><tr><td>Mood</td><td>Quiet, melancholic, disorienting, unsettling but not horror.</td></tr><tr><td>Environment</td><td>Contained hospital room and limited connected space if<br>needed.</td></tr><tr><td>Puzzle</td><td>Simple object-based puzzle using clearly signposted clues;<br>exact object sequence to be confirmed.</td></tr><tr><td>Pressure</td><td>Introduce low-intensity environmental feedback; avoid<br>overwhelming the player while teaching controls.</td></tr><tr><td>Completion</td><td>Introductory puzzle solved; exit/transition becomes<br>available.</td></tr><tr><td>Assets</td><td>Room shell, bed, door, hospital details, narrative objects,<br>prompts, lighting/audio states.</td></tr><tr><td>Acceptance test</td><td>A first-time player learns the controls and completes the<br>level without external instructions.</td></tr></table>


7.2 Level 2 - The Family Memory (Provisional)



<table><tr><td>Field</td><td>Initial plan</td></tr><tr><td>Purpose</td><td>Reveal the evening before the accident and complicate the<br>player's understanding of the family conflict.</td></tr><tr><td>Mood</td><td>Familiar domestic space made emotionally unstable<br>through lighting, layout, sound, and memory fragments.</td></tr><tr><td>Environment</td><td>Contained family location, potentially centered on the living<br>room or another story-critical space.</td></tr><tr><td>Puzzle</td><td>Symbolic object arrangement or sentence reconstruction<br>using environmental evidence.</td></tr></table>

---

<!-- Page 9 -->



<table><tr><td>Perspective</td><td>Show a shared event with changed contextual cues to communicate differing interpretations.</td></tr><tr><td>Pressure</td><td>Escalate at selected story beats; any wrong-answer effect must remain fair and understandable.</td></tr><tr><td>Completion</td><td>Enough of the argument is reconstructed to unlock the next stage.</td></tr><tr><td>Acceptance test</td><td>Players can describe the main disagreement and recognize multiple perspectives.</td></tr></table>  


#### 7.3 Level 3 - The Crash and Acceptance (Provisional)  



<table><tr><td>Field</td><td>Initial plan</td></tr><tr><td>Purpose</td><td>Bring memory fragments together and deliver emotional resolution.</td></tr><tr><td>Mood</td><td>Initially distorted and tense, gradually clearer as evidence connects.</td></tr><tr><td>Environment</td><td>Symbolic accident-memory space; reuse established assets and motifs where possible.</td></tr><tr><td>Puzzle</td><td>Final reconstruction puzzle using previously established clues; avoid introducing a new mechanic at the climax.</td></tr><tr><td>Pressure</td><td>Strongest planned pressure sequence, with clear warning and fair recovery.</td></tr><tr><td>Completion</td><td>Final puzzle resolved and intended ending reached.</td></tr><tr><td>Acceptance test</td><td>Players can explain the key events and understand the ending without an external explanation.</td></tr></table>  


### 7.4 Level Design Rules  


Each level has one primary narrative question and a clear completion condition. Introduce mechanics in a low- risk context before requiring them for progression. Every critical clue must be available in the level or an earlier accessible memory. Optional props should not distract from critical clues. Reuse interaction logic, puzzle components, materials, and sound cues. A level counts as complete only when it is playable from entry to exit in a packaged build.  


### 8. Art Direction  


### 8.1 Visual Identity  


The desired direction is stylized 3D with hand- painted PBR qualities: soft brush- like surface treatment, slightly rounded proportions, believable materials, and warm, realistic lighting. The world should feel melancholic, beautiful, and psychologically distorted, not cartoonish and not conventionally horrific.

---

<!-- Page 10 -->


## 8.2 Visual Principles  


8.2 Visual Principles- Maintain consistent material response and lighting across characters, props, and environments.- Use intentional distortion: altered proportions, repeated motifs, misplaced objects, asymmetry, and subtle space changes.- Keep character faces grounded and recognizable rather than anime- styled.- Use a restricted palette per level and reserve stronger changes for meaningful story beats.- Give critical objects readable silhouettes, contrast, or placement.- Prioritize cohesive assets and efficient geometry over photorealism or unnecessary polygon count.  


## 8.3 Asset Quality Tiers  



<table><tr><td>Tier</td><td>Use</td><td>Effort</td></tr><tr><td>Hero</td><td>Story-critical objects and close-up interactive props; visible characters.</td><td>Highest detail and polish within budget.</td></tr><tr><td>Environment</td><td>Walls, doors, furniture, hospital and family-room set dressing.</td><td>Consistent materials, readable silhouettes, optimized geometry.</td></tr><tr><td>Background</td><td>Distant props and decorative set dressing.</td><td>Simplified models/materials; no unnecessary interaction logic.</td></tr></table>  


## 9. Character Design and Animation Scope  


## 9.1 Character Clothing  


The main characters will wear simple, realistic clothing appropriate to their ages and personalities. The teenage protagonist will wear casual everyday clothing, while the father and mother will wear ordinary adult clothing that reflects their family roles. Character designs will follow the game's stylized 3D art direction, using slightly simplified proportions, soft textures, and believable materials. Clothing designs will remain consistent across related scenes unless a narrative event requires a change.  


## 9.2 Character Rigging and Animation  


All humanoid characters will use standard skeletal rigs suitable for Unreal Engine. Animation will focus on essential movements, including walking, standing, turning, interacting with objects, and basic gestures. Additional animations will be created for important narrative moments, such as the family argument and emotional memory sequences. The project will prioritize reusable animations and practical implementation over complex or highly detailed character animation.  


## 9.3 Facial Animation and Expressions  


Facial animation will focus on communicating emotions relevant to the narrative, including sadness, frustration, exhaustion, confusion, and regret. Basic facial expressions and body language will be used to support important story moments. Full dialogue lip- sync and highly detailed facial animation will only be implemented if time and technical resources allow.  


## 9.4 Character Visibility During Gameplay  


The game will primarily use a first- person perspective. The protagonist's full body will therefore not need to remain visible during gameplay, although hands or other body parts may be shown

---

<!-- Page 11 -->


during interactions when appropriate. The father and mother will appear in selected narrative sequences and memories when their presence is important to understanding the story. Environmental storytelling, dialogue, sound, and changes in the surrounding environment will also communicate events without requiring every moment to be shown through fully animated characters.  


### 9.5 Production Constraints  


Character modelling, rigging, animation, and implementation will be planned according to the team's available time and resources. Priority will be given to visual consistency, emotional readability, and the needs of the gameplay and narrative. Complex animations will be reserved for scenes where they provide meaningful value to the player's experience.  


## 10. Audio Direction  


- Use ambient room tone to establish location and emotional atmosphere.- Create distinct sound cues for interaction, puzzle progress, memory activation, and pressure changes.- Use filtering, silence, and spatial placement to suggest emotional instability.- Use limited dialogue/voice elements only where necessary; full professional voice acting is out of scope.- Avoid sudden loud sounds that do not serve the narrative.- Provide separate master/music/SFX controls if feasible.  


## 11. UI and Accessibility  


## 11.1 Minimal UI  


- Interaction prompt shown only when relevant.- Simple inspection view with a clear close/return action.- Puzzle interface shows available pieces, selections, and completion feedback.- Pause menu with resume, settings, and quit.- Pressure indicator is optional if environmental feedback communicates state consistently.  


## 11.2 Accessibility and Comfort  


- Allow sensitivity adjustment where practical.- Avoid prolonged forced camera movement and excessive screen shake.- Do not rely on color alone to distinguish states.- Keep text readable and give players enough time to read clues.- Do not communicate critical information exclusively through audio.- Consider an option to reduce intense distortion if feasible.  


## 12. Technical Design  


## 12.1 Platform  


Unreal Engine is the development platform for gameplay, 3D environments, environmental storytelling, and audiovisual effects.

---

<!-- Page 12 -->


## 12.2 Implementation Approach  


12.2 Implementation Approach- Build reusable interaction and inspectable- object logic before creating large amounts of content.- Represent puzzle state explicitly: unsolved, in progress, solved; persist state where transitions require it.- Use shared components/data-driven references for interactables where practical.- Separate pressure logic from individual effects so one state can drive lighting, audio, and distortion consistently.- Use transitions/checkpoints to prevent a single failed interaction from forcing a full restart.- Use version control, agreed branch/merge rules, and regular packaged builds.  


## 12.3 Proposed High-Level Architecture  



<table><tr><td>Component</td><td>Responsibility</td></tr><tr><td>Player Character / Controller</td><td>Movement, camera, interaction input, player-facing feedback.</td></tr><tr><td>Interaction Component</td><td>Detect interactables, show prompts, invoke inspect/use action, validate range.</td></tr><tr><td>Interactable Base / Interface</td><td>Shared behavior for objects that can be inspected, carried, or activated.</td></tr><tr><td>Puzzle Manager / Puzzle Actors</td><td>Track puzzle state, validate solutions, trigger completion events.</td></tr><tr><td>Memory Trigger</td><td>Activate memory fragments or environmental transitions.</td></tr><tr><td>Pressure Manager</td><td>Track pressure state and broadcast changes to audio/visual systems.</td></tr><tr><td>Environment Response Components</td><td>Apply lighting, audio, material, and authored layout changes.</td></tr><tr><td>Level Flow Manager</td><td>Control entry, completion, transitions, and persistent state.</td></tr><tr><td>UI Layer</td><td>Prompts, inspection/puzzle UI, pause/settings, feedback.</td></tr></table>  


This is a logical breakdown, not a requirement to create a separate Blueprint for every component. Combine small systems where appropriate.  


## 12.4 Performance and Build Requirements  


12.4 Performance and Build Requirements- Target at least 60 FPS on designated development hardware.- Test packaged builds, not only editor play sessions.- Use collision meshes and asset simplification/LODs where needed.- Avoid unnecessary real- time lights, expensive post- processing, and excessive transparent effects.- Profile representative scenes early.- Record tested hardware and build configuration in the final report.  


## 13. Content and Assets  



<table><tr><td>Content group</td><td>Minimum requirement</td><td>Notes</td></tr></table>

---

<!-- Page 13 -->



<table><tr><td>Levels</td><td>Three playable, connected levels.</td><td>Each needs entry, objective, puzzle progression, and completion transition.</td></tr><tr><td>Player</td><td>First-person movement and interaction.</td><td>Visible full-body model only if the design requires it.</td></tr><tr><td>Family characters</td><td>Character assets required for planned memory sequences.</td><td>Keep animation/facial performance scope realistic.</td></tr><tr><td>Interactive props</td><td>All objects required for inspection, carrying, placement, or puzzles.</td><td>Track in an asset register.</td></tr><tr><td>Environments</td><td>Hospital and story-critical memory environments.</td><td>Reuse modular props/materials where possible.</td></tr><tr><td>Audio</td><td>Ambient layers, interaction cues, memory cues, pressure states.</td><td>Consistent naming and trigger rules.</td></tr><tr><td>UI</td><td>Prompts, puzzle interface, pause/settings, feedback.</td><td>Readable and consistent.</td></tr><tr><td>Documentation</td><td>GDD, level sheets, technical notes, test cases, final report.</td><td>Keep updated during development.</td></tr></table>  


## 14. Team Workflow  



<table><tr><td>Team Member</td><td>Primary Responsibilities</td><td>Specific Tasks</td></tr><tr><td>Developer 1 — Core Gameplay &amp;amp; Interaction</td><td>Player controls and interaction</td><td>Player Character, Player Controller, Enhanced Input, interaction component, interactable objects, object inspection, pickup/prop mechanics, and interaction interfaces.</td></tr><tr><td>Developer 2 — Gameplay Systems &amp;amp; Progression</td><td>Puzzles, memory, and game progression</td><td>Puzzle framework, sentence construction, Memory Echo System, story events, level progression, emotional pressure system, and save/load functionality.</td></tr><tr><td>Developer 3 — Environment, 3D &amp;amp; Integration</td><td>3D assets, environments, and presentation</td><td>Character modelling, environment modelling, materials, lighting, environmental transformation, audio/VFX integration, and helping integrate the gameplay systems into the levels.</td></tr><tr><td>Scriptwriter</td><td>Narrative and dialogue</td><td>Main storyline, character backgrounds, dialogue, memory sequences, narrative progression across levels,</td></tr></table>

---

<!-- Page 14 -->


puzzle text, and consistency of the emotional themes.  


Create or source background music, environmental ambience, and sound effects; design audio for memory sequences and emotional pressure; organize audio assets; and collaborate with developers to integrate audio into Unreal Engine.  


Character movement, gestures, emotional body language, facial expressions, and animations for important story sequences, depending on availability.  


## 14.1 Weekly Workflow  


25. Plan the week's work from a prioritized backlog.  


26. Assign each task an owner, priority, estimate, and acceptance criteria.  


27. Integrate into the shared project regularly.  


28. Test the integrated build and record defects.  


29. Review milestones, risks, and dependencies.  


30. Demonstrate a playable result at the end of each meaningful iteration.  


## 14.2 Definition of Done  


Feature works in the integrated project and packaged build.  


Expected and failure cases have been tested.  


Existing level progression still works.  


Required assets, feedback, and documentation are included.  


Team has reviewed it and updated task status.  


## 15. Testing and Acceptance Criteria  



<table><tr><td>Area</td><td>Acceptance criterion</td></tr><tr><td>Level completion</td><td>All three levels can be entered, completed, and exited in intended sequence.</td></tr><tr><td>Movement and interaction</td><td>Player can move, inspect, interact, and place required objects without blocking progression.</td></tr><tr><td>Puzzle logic</td><td>Correct solutions trigger expected results; wrong solutions remain recoverable.</td></tr><tr><td>Memory reconstruction</td><td>Required fragments trigger under intended conditions and reveal planned information.</td></tr><tr><td>Pressure system</td><td>Pressure changes according to authored triggers, communicates state, and does not obscure clues.</td></tr></table>

---

<!-- Page 15 -->



<table><tr><td>Narrative comprehension</td><td>At least 10 playtesters; target at least 80% identify key events and understand different perspectives.</td></tr><tr><td>Performance</td><td>Target at least 30 FPS on designated development hardware in representative scenes.</td></tr><tr><td>Stability</td><td>No known critical bug prevents level completion.</td></tr><tr><td>Usability</td><td>Players understand interaction prompts and puzzle feedback without external explanation.</td></tr></table>  


## 15.1 Playtest Procedure  


15.1 Playtest Procedure31. Recruit at least 10 playtesters when an end-to-end build is available.32. Give a neutral introduction without explaining the story or solutions.33. Observe missed clues, confusing prompts, pressure spikes, and stuck points.34. Ask players to describe the events leading to the accident and explain the family conflict from more than one perspective.35. Collect ratings on puzzle clarity, atmosphere, control usability, and narrative engagement.36. Fix progression blockers first and retest affected sections.  


## 15.2 Bug Severity  



<table><tr><td>Severity</td><td>Definition</td><td>Response</td></tr><tr><td>Critical</td><td>Crash, progression failure, or inability to finish a level.</td><td>Fix before release candidate.</td></tr><tr><td>High</td><td>Core puzzle/interaction fails or story-critical information is inaccessible.</td><td>Fix before final playtest/build.</td></tr><tr><td>Medium</td><td>Confusing feedback, noticeable performance issue, or non-blocking visual/audio bug.</td><td>Prioritize by impact and time.</td></tr><tr><td>Low</td><td>Minor cosmetic issue or polish opportunity.</td><td>Address after higher-priority issues.</td></tr></table>  


## 16. Risks and Scope Control  



<table><tr><td>Risk</td><td>Impact</td><td>Mitigation</td></tr><tr><td>Art takes longer than expected</td><td>Incomplete/inconsistent environments.</td><td>Set a visual target in the vertical slice; reuse modular assets; prioritize hero assets.</td></tr><tr><td>Puzzles are unclear</td><td>Players get stuck or misunderstand story.</td><td>Prototype early; test outside the team; improve feedback before adding complexity.</td></tr></table>

---

<!-- Page 16 -->



<table><tr><td>Pressure effects obscure clues</td><td>Unfairness and accessibility issues.</td><td>Keep clues legible; tune thresholds; provide warning and recovery.</td></tr><tr><td>Narrative is hard to follow</td><td>Players miss the accident/conflict context.</td><td>Give each level a clear narrative question and test comprehension.</td></tr><tr><td>Scope expansion</td><td>Three levels miss deadline.</td><td>Keep extra levels, branching, combat, and ports out of scope.</td></tr><tr><td>Integration conflicts</td><td>Systems fail together despite working separately.</td><td>Integrate continuously; use version control and packaged builds.</td></tr><tr><td>Performance problems</td><td>Target frame rate missed.</td><td>Profile early; optimize lighting, materials, geometry, and effects.</td></tr><tr><td>Knowledge silos</td><td>A system is blocked when its owner is unavailable.</td><td>Write short technical notes, review work, and share knowledge.</td></tr></table>  


## 16.1 Change Control  


Evaluate proposed changes against three questions: Does it support the central player experience? Can it be implemented and tested in the timeline? What will be removed or simplified to make room? Defer additions that threaten completion of the three planned levels.  


## 17. Milestones  



<table><tr><td>Phase</td><td>Dates from proposal</td><td>Exit condition</td></tr><tr><td>Project proposal</td><td>22–26 Oct 2026</td><td>Proposal completed and approved.</td></tr><tr><td>Literature review and market visibility</td><td>26–31 Oct 2026</td><td>Related work and design references documented.</td></tr><tr><td>Requirements and game design</td><td>1–10 Nov 2026</td><td>GDD, level designs, requirements, technical direction, and responsibilities finalized.</td></tr><tr><td>Prototype and vertical slice</td><td>10 Nov–31 Dec 2026</td><td>Representative Level 1 section demonstrates visuals, interaction, puzzle logic, and atmosphere.</td></tr><tr><td>Full game production</td><td>1 Jan–1 May 2027</td><td>Three playable levels integrated with required assets, puzzles, narrative, and audiovisual effects.</td></tr><tr><td>Testing, polish, final submission</td><td>1 May–15 Jun 2027</td><td>Final build tested; performance and narrative clarity reviewed; documentation/presentation completed.</td></tr></table>  


Planning note: the proposal places the end of production and start of testing on the same date (1 May 2027). Treat this as a handover milestone and freeze critical content before final testing.

---

<!-- Page 17 -->


## 17.1 Vertical Slice Exit Criteria  


17.1 Vertical Slice Exit Criteria- One representative section is playable start to finish.- Core movement and interaction are reliable.- At least one representative puzzle is completable.- A memory event and environmental response are integrated.- Visual style, lighting, audio, and performance are reviewed.- Reusable systems/assets are documented before scaling production.  


## Final Design Principle  


Final Design PrincipleThe project succeeds when the three levels form a coherent, polished, completable emotional journey. Every mechanic, asset, sound, and puzzle should serve that experience. When time is limited, prioritize clarity, narrative integration, stability, and consistent visual quality over new features.