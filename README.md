# ToneWheelSine

*ToneWheelSine* is a Synth VST/AU using JUCE framework (http://www.juce.com)

*ToneWheelSine* is based on a hammond organ, hence the name, but it goes a little further :
there is 9 drawbars representing each one harmonic in that order :
- Sub harmonic
- 5th 
- Main
- 8th
- 12th
- 15th
- 17th
- 19th

With the harmonic selector, the user can choose between "Pure harmonics" and "Tempered harmonics". 

In the pure mode, all harmonics are reel harmonics (ie multiples of the main note frequency). If the note frequency is f, then the harmonics are (f/2, 1.5f, f, 2f, 3f, 4f, 5f, 6f, 8f).

In tempered mode, the harmonics are based on the notes, and are as follow:
- the lower octave
- the fifth (5th)
- the octave (8th)
- the octave fifth (12th)
- the octave's octave (15th)
- the octave's octave's third (17th)
- the octave's octave's fifth (19th)
- and another octave (22th)

For each harmonics, the user can fine tune (or detune) the phase with the first ligne of rotary knob, choose between sine and triangle waveform using the wave switch, and control the amount of signal from this harmonic going through the tremolo.

The tremolo speed and depth are controlled by two rotary knobs

Finally the volume knob allows you to adjust the overall volume.

The plugin has yet been tested in Logic X on MacOs 10.9.5.
