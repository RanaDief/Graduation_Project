# Memory Echoes

## Overview

Memory Echoes are short fragments of the player's memories that appear during exploration.

They are triggered by specific objects or areas in the environment and provide small pieces of story, emotional context, puzzle clues, or atmosphere.

Memory Echoes are not collectible items. They are predefined events placed in the environment.

The system is intentionally simple so it can be implemented and reused easily across all levels.

---

## Purpose

Memory Echoes are used to:

- Provide environmental storytelling.
- Reveal small pieces of the player's memories.
- Give clues for environmental puzzles.
- Show the player's relationship with his parents.
- Connect objects with past events.
- Build the emotional atmosphere of each level.
- Gradually reveal information about the accident and the events before it.

Memory Echoes should provide information without interrupting gameplay for too long.

---

## Basic Mechanic

The basic Memory Echo interaction is:

**Interact → Echo Plays → Simple Visual Appears → Echo Ends → Continue Exploring**

The player interacts with an important object or location.

A short memory fragment is then played through audio while a simple visual representation appears.

After the Echo finishes, the player returns to normal exploration.

---

## Triggering

Memory Echoes are primarily triggered through interaction with predefined objects.

Examples:

- Interacting with a family photograph.
- Inspecting a telephone.
- Looking at the clock.
- Interacting with the father's jacket.
- Approaching a specific location.
- Inspecting an object connected to an important memory.

Each Echo should have a clearly defined trigger.

The system should not require complex detection or procedural behavior.

### Recommended Implementation

Each Echo can use a simple interaction setup:

```text
Object
    ↓
Player Interacts
    ↓
Memory Echo Trigger
    ↓
Play Audio
    ↓
Show Simple Visual
    ↓
Echo Ends