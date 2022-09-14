# diodine
a distortion VST based on physical diode characteristics

currently supported: \
- forward, reverse, and bidirectional diodes
- variable forward voltage
- variable breakdown voltage
- gain
- mix
- built-in tanh saturation (will likely be switched to a gentler algorithm)

planned: \
- model reverse recovery w/ variable t_rr
- waveshaper graph to show forward/reverse voltage
- reverse recovery graph to show i_diode over t_rr
  - w/ variable load impedance
- circuit diagram w/ interactive switches, gain, mix
