import subprocess
import time
import os
import signal

process = subprocess.Popen(["python", "simpleaudio_play.py",
    "songs/Taylor-Swift-You-Belong-With-Me.wav"])
print(process.pid)

time.sleep(10)
process.kill()
