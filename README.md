# AssettoCorsaEnchanter

AssettoCorsaEnchanter is a tool designed to enhance the realism of Assetto Corsa, a popular racing simulation game.

**WARNING**:
AssettoCorsaEnchanter is still in its experimental development phase. Direct manipulation of Assetto Corsa's process memory is complex and may lead to unexpected behavior in the game. Use this tool with caution. For any feature requests or to report bugs, please feel free to open an issue.

### Showcase video
https://youtu.be/SNPz60kWrdo?si=aMTTx3hpICzC_Wu9

### Ability to stall
Currently, Assetto Corsa does not support realistic stalling. Even though the car drops to 0 rpm, all it takes is pressing the accelerator and the car starts moving again. 
This tool will allow the car to actually stall making it impossible to move the car using the accelerator. To turn the engine on again you can hold the **backspace** button.

### Ability to roll at low speeds
Assetto Corsa prevents the cars from moving when their speed is roughly below 5 m/s. This tool removes that constraint, leading to several improvements:
- Cars can start moving by merely slipping the clutch.
- Cars can roll backward on inclined or declined surfaces.
- Gradual stopping feels more natural, without the abrupt braking effect.
- Smooth movement is possible at speeds below 5 m/s.

### How it works
The tool interfaces directly with the Assetto Corsa process in memory, patching specific addresses and instructions responsible for the aforementioned effects. It does not alter any files in the Assetto Corsa directory, ensuring the integrity of the game's core files.

### How to use
Launch AssettoCorsaEnchanter before or after starting Assetto Corsa. The tool will automatically detect the game running in memory. 
Specific parameters can be adjusted in the config.txt file, which should be located in the same directory as the AssettoCorsaEnchanter executable.

### config.txt:
- _should_stall_: Enables or disables car stalling (true/false).
- _should_roll_: Allows cars to roll at low speeds (true/false).
- _stall_threshold_: Sets the RPM below the car's idle rate needed for the car to stall (int).
- _should_use_easy_stall_: Overrides stall threshold, in order to stall the car its RPM have to drop below 350 (true/false).

### Known issues:
Some cars have weird behavior when the _should_roll_ setting is enabled.

