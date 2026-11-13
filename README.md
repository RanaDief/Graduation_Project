# Words We Never Said

Shared development starting point for Rana Dief, Mahmoud Amr, and Osama Alashri.
Engine: Unreal Engine 5.8.4. Blueprint-only project; no C++ compiler required to open it.

## Open the project

Open `WordsWeNeverSaid.uproject` in Unreal 5.8.4. On this Linux machine, run:

```bash
./Tools/open_editor.sh
```

The editor opens `L_Development`: a plain floor, a light, and a Player Start for testing your work. Play currently uses Unreal's default flying pawn. Building the first-person character is the gameplay developer's first task.

`Core/BP_GameMode` and `Core/BP_GameInstance` are empty children of Unreal's built-in classes, already assigned in Project Settings. There are no custom mechanics, HUD, puzzles, checkpoints, story sequences, or finished levels.

## Where your work goes

All shared content lives under `Content/WordsWeNeverSaid`.

| Area | Folders |
| --- | --- |
| Gameplay and interaction | `Player`, `Player/Input`, `Interaction`, `UI` |
| Systems and progression | `Puzzles`, `Narrative/Memories`, `Pressure`, `Save`, `Data` |
| Environment and integration | `Environment`, `Art`, `Audio`, `Maps` |
| Shared project framework | `Core` |
| Personal experiments | `Developers/Gameplay`, `Developers/Systems`, `Developers/Environment` |

`Maps/Level01`, `Level02`, and `Level03` reserve locations for the three planned levels. They contain no authored maps yet. Their names, layout, puzzles, and narrative are for the team to decide. Enable **Show Empty Folders** in Content Browser settings to see reserved folders before assets are added.

Read `Docs/TeamWorkflow.md` together before starting. The supplied design document is preserved in `Docs/GameDesignDocument.md`.

## Setup status

Enhanced Input is enabled for the player developer. Editor Python and Epic's MCP toolsets are available for development assistance. The launch script starts MCP on loopback port 8017. This agent session could not connect to MCP because its network sockets are restricted.

The workspace was generated and saved through Unreal's headless editor. `Build/workspace_check.json` records the saved assets and map reload. A rendered preview and gameplay validation have not been performed; there is no custom gameplay yet.

The previous prototype is outside this project; its location is recorded in `Docs/PreviousPrototype.txt`.
