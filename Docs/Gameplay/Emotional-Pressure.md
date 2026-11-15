# Emotional Pressure

## Overview

Emotional Pressure is a core gameplay system that represents the psychological stress experienced by the player while confronting difficult memories.

Pressure connects the player's actions to changes in the game's audiovisual environment.

It is not a traditional health system.

Instead, it represents the player's psychological state and becomes more intense when the player is exposed to emotionally difficult situations.

The system is designed to:

- Create psychological tension.
- Make emotionally intense gameplay mechanically meaningful.
- Change the environment based on the player's psychological state.
- Encourage the player to understand and confront memories.
- Provide feedback without relying entirely on a traditional UI meter.

---

# Pressure Value

Emotional Pressure is represented internally as a value between:

**0 – 100**

Where:

- **0** represents a completely stable psychological state.
- **100** represents maximum psychological overload.

The value changes based on specific gameplay events.

Normal exploration does not continuously increase Pressure.

Pressure should primarily change when the player interacts with emotionally significant content.

---

# Pressure Increase

Pressure can increase when the player:

- Experiences an intense memory.
- Confronts a painful event.
- Replays an emotionally difficult memory.
- Makes certain emotionally aggressive or avoidant choices.
- Fails specific emotionally significant interactions.
- Remains inside heavily distorted memory areas for too long.

The amount of Pressure added depends on the intensity of the event.

### Example

| Event | Pressure Effect |
|---|---:|
| Minor puzzle mistake | Small increase |
| Incorrect emotional interaction | Small increase |
| Intense memory | Moderate increase |
| Major emotional confrontation | Moderate increase |
| Extremely intense memory | Large increase |
| Repeated exposure to painful memory | Increasing effect |

Pressure values should be tuned during playtesting.

The system should avoid making normal experimentation overly punishing.

---

# Pressure Decrease

Pressure can decrease when the player reaches moments of psychological stability.

Pressure may decrease after:

- Successfully completing an important puzzle.
- Understanding a memory.
- Successfully reconstructing a memory.
- Making an emotionally constructive choice.
- Accepting a difficult memory.
- Completing an important gameplay section.
- Reaching a major checkpoint.

Pressure reduction should feel like a result of progress rather than simply waiting for a timer.

---

# Memory Echoes and Pressure

Memory Echoes do **not** directly increase Emotional Pressure.

Memory Echoes are primarily used for:

- Exploration.
- Context.
- Environmental storytelling.
- Puzzle clues.
- Discovering information about memories.

The player should be encouraged to investigate Memory Echoes without being punished for exploring them.

The distinction is:

**Exploring memories is safe.**

**Confronting painful emotions creates Pressure.**

---

# Pressure States

The Pressure value is divided into several psychological states.

## Low Pressure

### Range

**0–39**

The player's psychological state is stable.

### Visual

- Normal lighting.
- Stable environment.
- Minimal visual distortion.
- Normal object behavior.

### Audio

- Clear dialogue.
- Normal environmental sounds.
- Normal breathing.
- Minimal distortion.

### Gameplay

The player can freely explore and interact with the environment.

---

# Medium Pressure

### Range

**40–69**

The player's psychological state begins becoming unstable.

### Visual

- Occasional light flickering.
- Subtle environmental distortion.
- Small changes in object appearance.
- Slight instability in memory scenes.

### Audio

- Louder breathing.
- Increased environmental sounds.
- Subtle audio distortion.
- Certain sounds become more noticeable.

### Gameplay

The player remains fully capable of interacting with the environment.

The changes are primarily used to communicate increasing psychological tension.

---

# High Pressure

### Range

**70–99**

The player is experiencing significant psychological stress.

### Visual

- Stronger environmental distortion.
- Unstable lighting.
- Memory fragments may shake or distort.
- Environmental objects may appear temporarily altered.
- Visual clarity may decrease.

### Audio

- Louder heartbeat.
- Heavy breathing.
- Distorted dialogue.
- Overlapping voices.
- Increased environmental noise.

### Gameplay

The player can still control the character normally.

The purpose of this state is to create tension rather than disable the player.

---

# Maximum Pressure

### Value

**100**

Maximum Pressure represents psychological overload.

When Pressure reaches 100:

1. The environment becomes severely distorted.
2. Audio becomes heavily distorted.
3. Memory elements begin collapsing.
4. The screen gradually fades to black.
5. The current psychological sequence ends.
6. The player returns to the latest checkpoint.

Maximum Pressure should function as a gameplay failure state rather than a permanent game over.

---

# Pressure Recovery

Pressure should be recoverable during normal gameplay.

Recovery can occur through meaningful progression rather than passive waiting.

Examples include:

- Completing a puzzle.
- Resolving a memory.
- Reaching a stable environment.
- Making a constructive emotional choice.
- Accepting a difficult situation.
- Completing a major gameplay objective.

Recovery allows the player to continue exploring without becoming permanently trapped at high Pressure.

---

# Pressure Feedback

The player should not need to constantly look at a numerical Pressure meter.

The environment communicates the current state.

### Visual Feedback

Pressure can be communicated through:

- Lighting.
- Screen distortion.
- Object movement.
- Memory instability.
- Environmental changes.
- Visual effects.

### Audio Feedback

Pressure can be communicated through:

- Breathing.
- Heartbeat.
- Voice distortion.
- Background noise.
- Environmental sounds.
- Audio intensity.

### Gameplay Feedback

Pressure changes should occur in response to recognizable actions.

The player should gradually understand:

**"What I am experiencing is affecting my psychological state."**

---

# Pressure and Gameplay

Emotional Pressure is not intended to replace the game's puzzles.

It acts as a secondary system that reacts to the player's interaction with emotionally significant content.

The primary gameplay remains:

**Explore → Inspect → Understand → Solve / Choose → Progress**

Emotional Pressure operates alongside this loop:

**Player Action → Emotional Impact → Pressure Change → Environmental Feedback**

This allows the psychological state of the character to become part of the gameplay experience.

---

# Pressure and Choices

Choices can affect Emotional Pressure when they represent emotionally significant responses.

A choice may:

- Increase Pressure.
- Decrease Pressure.
- Leave Pressure unchanged.

The effect should depend on the emotional context of the choice.

There should not always be an obvious "correct" answer.

The system is designed to reflect the emotional consequences of the player's response rather than judge the player morally.

---

# Pressure and Puzzle Failure

Some puzzles may cause a small Pressure increase when the player performs an incorrect action.

This should only be used when the failure is relevant to the psychological experience.

Incorrect actions should generally:

- Provide feedback.
- Allow the player to retry.
- Avoid large Pressure penalties.
- Avoid creating unnecessary frustration.

The first few interactions with a mechanic should have especially low penalties so that players can learn how the system works.

---

# Pressure and Memory Exposure

Extended exposure to emotionally intense memories can increase Pressure.

This should be controlled carefully.

The player should not be punished simply for taking time to explore.

Pressure should increase primarily when:

- The memory is actively playing.
- The player remains inside a heavily distorted section.
- The player repeatedly confronts the same painful event.

This prevents the system from becoming a simple countdown timer.

---

# Checkpoint Interaction

Checkpoints work together with the Pressure system.

If Pressure reaches 100:

- The current sequence collapses.
- The player returns to the latest checkpoint.
- Major completed progress is preserved.
- The player can attempt the section again.

The checkpoint system prevents Pressure from creating excessive repetition.

---

# Difficulty Tuning

Pressure values should be tuned during playtesting.

Important variables include:

- Pressure gained from each event.
- Pressure recovered from successful actions.
- Duration before environmental distortion increases.
- Thresholds between Pressure states.
- Maximum Pressure behavior.
- Checkpoint frequency.

The system should create tension without making the player feel constantly punished.

The intended experience is:

**Low Pressure → Stable**

**Medium Pressure → Uncomfortable**

**High Pressure → Unstable**

**100 Pressure → Overload**

---

# Core Design Principles

## 1. Pressure Represents Emotion

Pressure represents psychological stress rather than physical damage.

## 2. Exploration Is Safe

Players should be encouraged to investigate the environment and discover memories.

## 3. Emotional Confrontation Has Consequences

Painful memories and emotionally intense situations can increase Pressure.

## 4. Feedback Should Be Diegetic

Whenever possible, the environment and audio should communicate Pressure rather than relying on a traditional HUD meter.

## 5. Failure Is Temporary

Maximum Pressure should return the player to a checkpoint rather than permanently ending the game.

## 6. Avoid Excessive Punishment

The system should create tension without discouraging experimentation.

## 7. Pressure Supports Progression

Successfully understanding and confronting memories should help stabilize the player's psychological state.

---

# Emotional Pressure Summary

Emotional Pressure is a dynamic psychological state ranging from **0 to 100**.

It reacts to emotionally significant gameplay and communicates the player's psychological condition through audiovisual changes.

The system follows:

**Emotional Event**

↓

**Pressure Changes**

↓

**Environment Reacts**

↓

**Player Recognizes Psychological State**

↓

**Player Continues / Resolves the Situation**

At maximum Pressure:

**Pressure = 100**

↓

**Psychological Overload**

↓

**Current Sequence Collapses**

↓

**Return to Checkpoint**