This is the repository for the motion control code (python and C) of a AGV built up with Raspberry Pi, arduino and encoded DC motor driven Mecanum wheels, which is controlled by a bluetooth joystick controller. 

## Controller - Raspberry Pi

### Enviroment Setup

Please install [mini-forge](https://github.com/conda-forge/miniforge) for Linux aarch64 (arm64) first, then:
```
conda activate
conda create -n agv python=3.10
conda activate agv
python -m pip install pygame
python -m pip install pyserial
```

