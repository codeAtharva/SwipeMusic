import sys
import time
import simpleaudio as sa
from optparse import OptionParser


def play_music(filename):
    wave_obj = sa.WaveObject.from_wave_file(filename)
    play_obj = wave_obj.play()
    play_obj.wait_done()

def parse():
    parser = OptionParser()
    _, args = parser.parse_args()
    return args[0]

if __name__ == "__main__":
    play_music(parse())
