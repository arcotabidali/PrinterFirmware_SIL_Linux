
from ctypes import c_double
from time import sleep
from plant_model import HeaterPlant

def test_heater_reaches_setpoint(fw):
    env = HeaterPlant(ambient_c=20.0)
    fw.firmware_set_ambient_temp(c_double(env.ambient))
    fw.firmware_cmd_heater_setpoint(c_double(60.0))

    for _ in range(80):
        fw.firmware_step()
        sleep(0.003)

    temp = fw.firmware_get_heater_temp()
    assert temp > 50.0, f"Heater too cold after warmup: {temp:.1f}C"

    fw.firmware_cmd_heater_setpoint(c_double(70.0))
    for _ in range(100):
        fw.firmware_step()
        sleep(0.003)

    temp2 = fw.firmware_get_heater_temp()
    assert temp2 > 62.0, f"Heater did not follow new setpoint: {temp2:.1f}C"
