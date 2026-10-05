# Flashback System

## Overview

The Flashback System is a gameplay and storytelling mechanic used to reveal fragments of the player's memories.

Flashbacks are short interactive or cinematic memory sequences triggered by significant player actions.

They provide emotional and narrative feedback while helping the player gradually understand the memories represented by the psychological world.

Flashbacks are not collectibles.

They are integrated directly into gameplay progression and are triggered when the player reaches meaningful moments.

---

# Purpose

The Flashback System is designed to:

- Reveal information about the player's memories.
- Provide feedback for meaningful gameplay actions.
- Strengthen emotional moments.
- Connect puzzles to the player's memories.
- Show relationships between characters and events.
- Provide contrast between positive and painful memories.
- Gradually make fragmented memories clearer.

Flashbacks should support gameplay rather than completely replace it.

---

# Flashback Triggers

A flashback can be triggered by a significant gameplay event.

Possible triggers include:

- Inspecting an important object.
- Completing a puzzle.
- Correctly reconstructing a memory.
- Completing a major interaction.
- Making a significant emotional choice.
- Reaching a major progression point.
- Interacting with a specific memory-related location.

Not every interaction should trigger a flashback.

Flashbacks should be reserved for meaningful moments.

---

# Flashback Types

The system supports several types of flashbacks.

## 1. Visual Flashback

A short visual sequence showing part of a memory.

The player may see:

- Characters.
- Locations.
- Objects.
- Actions.
- Environmental details.

Visual flashbacks can be presented as short cinematic sequences or first-person memory scenes.

---

## 2. Audio Flashback

A memory is communicated primarily through sound.

Examples include:

- Dialogue.
- Voices.
- Footsteps.
- Phone conversations.
- Environmental sounds.
- Music.
- Background noise.

Audio flashbacks can occur while the player remains in the current environment.

---

## 3. Environmental Flashback

The current environment temporarily transforms into a memory.

Elements of the environment may:

- Change appearance.
- Change lighting.
- Change position.
- Appear or disappear.
- Become distorted.
- Transition into a previous state.

The player experiences the memory without necessarily leaving the current gameplay space.

---

## 4. Interactive Flashback

The player is temporarily placed inside a memory and can interact with it.

The player may:

- Walk through the memory.
- Observe characters.
- Interact with specific objects.
- Trigger additional memory events.

Interactive flashbacks should remain short and focused.

They should not introduce completely new gameplay systems unless necessary.

---

# Flashback Structure

A typical flashback follows:

**Trigger → Transition → Memory → Resolution → Return**

### 1. Trigger

The player performs an action that activates the flashback.

### 2. Transition

The game provides a visual or audio transition.

Examples:

- Screen fading.
- Environmental distortion.
- Camera transition.
- Sound transition.
- Lighting change.

### 3. Memory

The memory sequence plays.

The player receives new information or experiences an emotional moment.

### 4. Resolution

The memory ends naturally.

It may:

- Fade away.
- Become distorted.
- Stop abruptly.
- Transition back into the environment.

### 5. Return

The player returns to normal gameplay.

The environment returns to its previous state unless the flashback caused a permanent progression change.

---

# Memory Clarity

Flashbacks can become clearer as the player progresses through the game.

Early memories may contain:

- Missing information.
- Visual distortion.
- Incomplete dialogue.
- Unclear locations.
- Short fragments.

Later memories can contain:

- Clearer visuals.
- Complete dialogue.
- More environmental details.
- Longer sequences.
- Additional perspectives.

This allows the player to gradually build a clearer understanding of the past.

---

# Positive and Painful Flashbacks

Flashbacks can represent both positive and painful memories.

## Positive Flashbacks

Positive memories provide emotional contrast.

They can show:

- Family connection.
- Support.
- Care.
- Ordinary happy moments.
- Positive relationships.

Positive flashbacks can also provide a sense of relief after difficult gameplay.

They may contribute to Pressure recovery when appropriate.

---

## Painful Flashbacks

Painful memories represent emotionally difficult events.

They can show:

- Arguments.
- Fear.
- Anger.
- Regret.
- Guilt.
- The accident.
- Emotional conflict.

Painful flashbacks can contribute to Emotional Pressure depending on their intensity.

The Flashback System itself does not automatically increase Pressure.

Pressure is determined by the emotional intensity of the specific event.

---

# Flashback Progression

Flashbacks should reveal information gradually.

A single flashback should not necessarily explain an entire event.

Instead, multiple flashbacks can provide different pieces of information.

For example:

**Fragment A**

↓

Provides context

↓

**Fragment B**

↓

Provides additional information

↓

**Fragment C**

↓

Connects the previous fragments

↓

**Complete Understanding**

This allows the player to construct an understanding of the past through gameplay.

---

# Flashbacks and Puzzles

Flashbacks can provide information that helps the player solve puzzles.

A flashback may reveal:

- Where an object was located.
- What happened before an event.
- The order of events.
- A character's action.
- A relationship between objects.
- A previously unknown detail.

The player should be able to remember or recognize this information when solving related gameplay challenges.

Flashbacks should therefore have gameplay value in addition to narrative value.

---

# Flashbacks and Memory Reconstruction

Flashbacks can be used as feedback after successful memory reconstruction.

When the player correctly reconstructs a memory:

1. The reconstructed memory becomes stable.
2. A flashback is triggered.
3. The player sees the restored event.
4. Additional information is revealed.
5. Gameplay resumes.

This creates a direct connection between:

**Player Understanding → Gameplay Success → Memory Restoration**

---

# Flashback Interruption

Flashbacks should generally be short and focused.

The player should not be forced to watch long cinematic sequences repeatedly.

A flashback may end early if:

- The relevant information has been delivered.
- The memory becomes unstable.
- The player reaches the end of the sequence.
- The game needs to return control to the player.

Important flashbacks can be longer when they serve as major emotional moments.

---

# Flashback Repetition

Previously experienced flashbacks should not normally replay in full.

If a player encounters the same memory again, the system can:

- Skip the sequence.
- Play a shorter version.
- Reveal an additional detail.
- Allow the player to continue immediately.

This prevents repeated gameplay sections from becoming tedious.

---

# Flashback Rewards

Flashbacks function as a reward for meaningful gameplay progression.

They can provide:

- New information.
- Emotional context.
- Puzzle clues.
- Character development.
- Pressure recovery.
- Environmental changes.
- Progress toward memory completion.

The player should feel that understanding the environment has produced a meaningful result.

---

# Flashback Visual Feedback

Flashbacks can use consistent visual language to distinguish memories from normal gameplay.

Possible effects include:

- Subtle color or lighting changes.
- Depth-of-field changes.
- Screen transitions.
- Environmental distortion.
- Memory overlays.
- Temporary changes in camera behavior.
- Gradual fading between reality and memory.

The effects should remain consistent enough for the player to recognize when a flashback is occurring.

---

# Flashback Audio Feedback

Audio is an important part of the Flashback System.

Possible audio elements include:

- Memory-specific music.
- Character voices.
- Echoing dialogue.
- Environmental sounds.
- Muffled sounds.
- Distorted sounds.
- Sudden silence.
- Breathing.
- Heartbeat.

Audio can also transition between normal gameplay and the memory.

---

# Flashback State

The game should track whether a flashback has been:

- Unseen.
- Currently playing.
- Completed.
- Previously experienced.

This allows the system to control repetition and progression.

Example state flow:

**Unseen → Triggered → Playing → Completed**

Once completed:

**Completed → Previously Experienced**

The system can then determine whether to replay the full sequence or provide a shorter version.

---

# Flashback and Player Control

Player control depends on the type of flashback.

### Cinematic Flashback

Player control is temporarily disabled.

The player watches the memory sequence.

### Environmental Flashback

Player control remains active.

The environment changes around the player.

### Interactive Flashback

Player control remains active and the player can interact with the memory.

The type of control should be chosen based on the purpose of the flashback.

---

# Flashback and Emotional Pressure

Flashbacks and Emotional Pressure are connected but remain separate systems.

A flashback does not automatically increase Pressure.

Instead, the emotional intensity of the flashback determines whether Pressure changes.

### Example

**Positive Memory**

→ Little or no Pressure increase

**Neutral Memory**

→ No significant Pressure change

**Painful Memory**

→ Moderate Pressure increase

**Extremely Intense Memory**

→ Large Pressure increase

This keeps the Flashback System responsible for memory presentation while the Emotional Pressure System controls psychological stress.

---

# Flashback Design Principles

## 1. Keep Flashbacks Purposeful

Every flashback should provide information, emotional context, or meaningful feedback.

## 2. Keep Them Short

Flashbacks should not unnecessarily interrupt gameplay.

## 3. Avoid Repetition

Previously seen memories should not repeatedly play in full.

## 4. Connect Them to Gameplay

Whenever possible, flashbacks should result from meaningful player actions.

## 5. Gradually Reveal Information

Memories should become clearer as the player progresses.

## 6. Use Positive and Negative Contrast

Positive memories should provide contrast to painful memories.

## 7. Keep Systems Separate

Flashbacks present memories.

Emotional Pressure represents psychological stress.

The two systems interact but should remain independently manageable.

---

# Core Flashback Flow

The general system can be represented as:

**Player Action**

↓

**Flashback Trigger**

↓

**Transition**

↓

**Memory Sequence**

↓

**Information / Emotional Feedback**

↓

**Flashback Resolution**

↓

**Return to Gameplay**

↓

**Progression**

Flashbacks therefore function as a bridge between the player's gameplay actions and the character's memories.