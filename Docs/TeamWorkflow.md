# Team starting agreement

Based on GDD sections 12–14. Assign the roles among yourselves; the document does not assign these roles to specific names.

## First tasks

| Role | First deliverable | Later work from the GDD |
| --- | --- | --- |
| Developer 1: gameplay and interaction | First-person Character, camera, Enhanced Input movement/look, tested on the development floor | Targeting, inspect/use interface, pickup/placement, UI prompts |
| Developer 2: systems and progression | Agree puzzle IDs, puzzle states, and completion events with Developer 1 | Sentence puzzles, memories, pressure, level flow, save/load |
| Developer 3: environment and integration | Agree scale and create a small modular room kit; build the first hospital blockout | Characters, materials, lighting, environmental responses, audio/VFX integration |

Agree the first interaction contract before making many props: who detects the target, who validates use, how completion is broadcast, and which state survives a map change. The GDD architecture is guidance, not a requirement to create a manager for every feature.

## Sharing the project

Use one repository for this folder. Share `Config`, `Content`, `Docs`, `Tools`, the `.uproject`, and Git settings. Generated `Saved`, `Intermediate`, `DerivedDataCache`, and `Binaries` are ignored.

Git LFS patterns are provided for Unreal binary assets. Each teammate installs Git LFS and runs `git lfs install` before adding assets. The shared repository is https://github.com/RanaDief/Graduation_Project.git. Clone with LFS enabled and use the same Unreal patch version. Fetch the existing team branches before starting work.

Use short feature branches such as `feature/player-movement`, `feature/puzzle-state`, and `feature/hospital-kit`. Pull before starting, keep commits focused, and have another teammate review before merging.

Unreal maps and Blueprints are binary files: agree one editor per shared asset at a time. Use separate development maps for parallel work. If your Git host supports LFS locks, lock shared maps/Blueprints before editing. Rename or move assets inside Unreal so references remain valid.

Do not commit private experiments from Developers into production maps without review. Integrate weekly, run the shared map, and make packaged builds at milestones as the GDD requests.

## Naming

Use `BP_` for Blueprints, `BPC_` for actor components, `BPI_` for interfaces, `WBP_` for widgets, `IA_` for input actions, `IMC_` for mappings, `L_` for maps, `SM_` for static meshes, `M_`/`MI_` for materials/instances, and `T_` for textures. Keep names descriptive and paths short.

## Decisions to resolve

- Confirm the three level names and their puzzle/narrative content.
- Confirm the target development hardware and FPS budget: sections 1/3/15 say 30 FPS; section 12.4 says 60 FPS.
- Decide pressure thresholds through prototyping. The GDD leaves failure/reset at maximum pressure open.
- Assign people to the three development roles and agree who owns shared assets.
- Agree the first weekly milestone.

## First milestone

A controllable first-person player in a small test room, with one inspectable object. Build that together before expanding into puzzles, memories, and full levels.
