# PrinterFirmware_SIL_Linux  
*A full Software-in-the-Loop (SIL) test framework for STM32 firmware on Linux*

---

## 📖 Overview

This project demonstrates how to compile an **entire STM32 firmware application** into a **Linux shared object (`.so`)** and test it in a **Software-in-the-Loop (SIL)** environment using **Python, pytest, and lightweight plant models**.

It mirrors how real QA teams validate embedded firmware (e.g., in printers, energy systems, or robotics) — before flashing hardware.

---

## ⚙️ Project Architecture

```
Python Test Harness (pytest, numpy, matplotlib)
          │
          ▼
libprinter_firmware.so (all STM32 firmware compiled for Linux)
+ HAL stubs (GPIO, ADC, Delay)
          │
          ▼
Simulated Plant Models (motor load, heater ambient, etc.)
```

Each test drives the firmware through exported C APIs (via `ctypes`), feeds in simulated inputs, executes multiple scheduler “steps,” and verifies that system behavior (RPM, temperature, etc.) matches expectations.

---

## 🧱 Folder Structure

```
PrinterFirmware_SIL_Linux/
├── Core/
│   ├── Inc/
│   │   ├── firmware.h          # Public firmware API (exposed to Python)
│   │   ├── system_state.h      # Global state machine and fault tracking
│   │   ├── paperfeed.h         # Paper feed motor controller interface
│   │   └── heater_control.h    # Heater control interface
│   └── Src/
│       ├── main.c              # Entry point for host-mode execution
│       ├── firmware_api.c      # Glue layer exposing firmware.h functions
│       ├── system_state.c      # Basic READY/INIT state transitions
│       ├── paperfeed.c         # Motor control logic (rpm, load response)
│       └── heater_control.c    # Heater control (ambient & setpoint)
│
├── SIL_Stubs/
│   ├── hal_stubs.c             # Replaces HAL GPIO/Delay functions
│   ├── mock_adc.c              # Stub for ADC reads
│   └── timebase_stub.c         # Provides a fake system tick (HAL_GetTick)
│
├── tests/
│   ├── conftest.py             # Pytest fixture loading libprinter_firmware.so
│   ├── plant_model.py          # Simple Python models for motor & heater
│   ├── test_paperfeed.py       # Verifies motor control under load conditions
│   └── test_heater.py          # Verifies heater setpoint & ambient response
│
├── reports/                    # Test results and plots (created at runtime)
├── docs/
│   └── architecture.png        # Visual diagram of Python↔Firmware↔Plant flow
│
├── Makefile                    # Builds the firmware .so for host testing
├── requirements.txt            # Python dependencies
└── README.md                   # (this file)
```

---

## 🧰 Toolchain and Dependencies

### 🔧 Build Tools
| Tool | Purpose |
|------|----------|
| **gcc** | Compiles firmware C code for host (Linux x86_64). |
| **make** | Automates build (creates `build/libprinter_firmware.so`). |
| **ctypes (Python stdlib)** | Loads and calls functions from `.so`. |

### 🐍 Python Packages (from `requirements.txt`)
| Package | Purpose |
|----------|----------|
| **pytest** | Core test framework for SIL regression. |
| **pytest-html** | Generates HTML test reports for QA. |
| **numpy** | Math utilities for plant simulation and numeric checks. |
| **matplotlib** | (Optional) Plot trends such as temperature vs. time. |
| **pandas** | (Optional) Structured test data / CSV handling. |

Install all packages:
```bash
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
```

---

## 🏗️ Building the Firmware for Host (SIL Mode)

Run:
```bash
make
```

This compiles **all `.c` files** (firmware + stubs) into:
```
build/libprinter_firmware.so
```

This `.so` contains the *entire firmware image* (minus hardware drivers), now callable from Python via `ctypes`.

---

## 🧪 Running SIL Tests

Run:
```bash
pytest -v --html=report.html --self-contained-html
```

### Test Categories
| Test | Description |
|------|--------------|
| `test_paperfeed.py` | Runs the paper feed motor controller through start/stop and load variations. Checks RPM response and decay. |
| `test_heater.py` | Verifies the heater reaches and tracks setpoint temperature under different ambients. |
| `plant_model.py` | Provides simple physical models for environment behavior. |

Outputs:
- `report.html` — summary of test results  
- (optional) plots or logs saved to `reports/`

---

## 🧩 How It Works (Execution Flow)

1. **Python test** loads the `.so`:
   ```python
   fw = CDLL("./build/libprinter_firmware.so")
   ```
2. Calls exposed firmware APIs:
   ```python
   fw.firmware_init()
   fw.firmware_cmd_paperfeed_start(1500.0)
   fw.firmware_step()
   rpm = fw.firmware_get_motor_rpm()
   ```
3. The `.so` executes the same C logic as your STM32 firmware, but using stubbed HAL functions (no hardware).
4. Python’s `plant_model` simulates environment feedback (e.g., motor load or ambient temp).
5. Assertions in `pytest` check firmware response against expectations.
6. The pipeline produces detailed HTML reports for QA traceability.

---

## 🧠 Extending the Framework

| Goal | How |
|------|-----|
| Add more peripherals | Create additional stubs in `SIL_Stubs/` |
| Add more test scenarios | Create new `test_*.py` files under `tests/` |
| Integrate into CI | Add `make && pytest` stages to Jenkins/GitHub Actions |
| Include coverage/linting | Add `pytest-cov`, `flake8` to `dev-requirements.txt` |
| Model complex physics | Expand `plant_model.py` (e.g., inertia, PID, noise) |

---

## 🚀 Continuous Integration Example

Typical Jenkins pipeline snippet:
```groovy
stage('SIL Build & Test') {
    sh '''
        make
        pytest -v --junitxml=results.xml --html=report.html --self-contained-html
    '''
    archiveArtifacts artifacts: 'report.html, results.xml', fingerprint: true
}
```

---

## 🧾 Credits

Created as a **reference implementation for Firmware QA Engineers** automating SIL verification of STM32 embedded systems using open-source tools.  
Tested on Ubuntu 22.04 LTS with GCC 11 and Python 3.12.
