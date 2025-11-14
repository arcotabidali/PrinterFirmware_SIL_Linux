
import pytest, os
from ctypes import CDLL, c_double, c_int

@pytest.fixture(scope="session")
def fw():
    so_path = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "build", "libprinter_firmware.so"))
    fw = CDLL(so_path)

    # --- set C function prototypes for correct ctypes conversion ---
    # Return types
    fw.firmware_get_heater_temp.restype = c_double
    fw.firmware_get_motor_rpm.restype = c_double
    fw.firmware_get_fault_code.restype = c_int
    fw.firmware_get_ready.restype = c_int

    # Void-returning functions: tell ctypes they return nothing
    fw.firmware_init.restype = None
    fw.firmware_step.restype = None
    fw.firmware_shutdown.restype = None
    fw.firmware_cmd_paperfeed_stop.restype = None

    # Argument types (helps validate/cast inputs)
    fw.firmware_set_ambient_temp.argtypes = [c_double]
    fw.firmware_cmd_heater_setpoint.argtypes = [c_double]
    fw.firmware_cmd_paperfeed_start.argtypes = [c_double]
    fw.firmware_set_motor_load.argtypes = [c_double]

    fw.firmware_init()
    yield fw
    fw.firmware_shutdown()
