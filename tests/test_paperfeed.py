
from ctypes import c_double
from time import sleep
from plant_model import PaperFeedPlant

def test_paperfeed_basic_tracking(fw):
    plant = PaperFeedPlant()
    fw.firmware_cmd_paperfeed_start(c_double(1500.0))

    for _ in range(50):
        fw.firmware_set_motor_load(c_double(plant.load))
        fw.firmware_step()
        sleep(0.005)

    rpm_nominal = fw.firmware_get_motor_rpm()
    assert rpm_nominal > 1000, f"RPM too low at nominal load: {rpm_nominal:.1f}"

    plant.disturb(4.0)
    for _ in range(50):
        fw.firmware_set_motor_load(c_double(plant.load))
        fw.firmware_step()
        sleep(0.005)

    rpm_loaded = fw.firmware_get_motor_rpm()
    assert rpm_loaded > 800, f"RPM collapsed under load: {rpm_loaded:.1f}"

    fw.firmware_cmd_paperfeed_stop()
    for _ in range(20):
        fw.firmware_step()
        sleep(0.002)

    rpm_stop = fw.firmware_get_motor_rpm()
    assert rpm_stop < 200, f"RPM did not decay after stop: {rpm_stop:.1f}"
