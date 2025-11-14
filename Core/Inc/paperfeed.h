
#ifndef PAPERFEED_H
#define PAPERFEED_H

void paperfeed_init(void);
void paperfeed_tick(void);
void paperfeed_start(double rpm_target);
void paperfeed_stop(void);
double paperfeed_get_rpm(void);
void paperfeed_set_load(double load_torque);

#endif /* PAPERFEED_H */
