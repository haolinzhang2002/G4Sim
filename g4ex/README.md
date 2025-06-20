# G4Ex: Minimal Geant4 Example Framework

A minimal yet fully functional Geant4 project template designed for beginners to understand the framework structure and serve as a foundation for custom simulation applications.

## 🔍 Key Features
- Complete Geant4 application structure in minimal code
- Modular implementation of essential components:
  - Detector Construction
  - Primary Generator
  - Physics List
  - Run/Event/Stepping Actions
  - Action Initialization
- CMake-based build system

## 🧰 Requirements
- Geant4 Toolkit (v10.7 or newer recommended)
- CLHEP library
- CMake 3.14+
- C++17 compliant compiler

## 🚀 Quick Start Guide

### 1. Clone the repository
```bash
git clone -b g4ex https://github.com/haolinzhang2002/G4Sim.git
cd g4ex
```

### 2. Build the project
```bash
mkdir build && cd build
cmake .. -DGeant4_DIR=/path/to/geant4/lib/Geant4-XX.X.X
make -j$(nproc)
```

### 3. Run the simulation
```bash
./g4ex
```

## 📁 Project Structure
```
src/
├── DetectorConstruction.cc       # Geometry definition
├── PrimaryGenerator.cc           # Particle source definition
├── PhysicsList.cc                # Physics processes configuration
├── RunAction.cc                  # Run management
├── EventAction.cc                # Event processing
├── SteppingAction.cc             # Step-level tracking
└── ActionInitialization.cc       # Action registration

include/
├── DetectorConstruction.hh
├── PrimaryGenerator.hh
├── PhysicsList.hh
├── RunAction.hh
├── EventAction.hh
├── SteppingAction.hh
└── ActionInitialization.hh
```

## 📚 Documentation
Each component follows the Geant4 recommended design patterns:
- **DetectorConstruction**: Defines the experimental geometry
- **PrimaryGenerator**: Implements particle source using G4ParticleGun
- **PhysicsList**: Configures electromagnetic physics processes
- **Action classes**: Demonstrates the Geant4 user action architecture

## 🧪 Simulation Features
- Basic detector geometry (simple box volume)
- Basic particle source distribution example (default: proton ray)
- Basic physics list including electromagnetic, strong and weak processes
