import serial
import sys
import os
import subprocess
import time


def right_process(songs, song_index, process):
    song_index+=1
    if song_index > len(songs) - 1:
        song_index = 0

    try:
        process.kill()
    except:
        pass

    process = subprocess.Popen(["python", "simpleaudio_play.py", 
            "songs/" + songs[song_index]])
    return song_index, process

def left_process(songs, song_index, process):
    song_index -= 1
    if song_index < 0:
        song_index = 0

    try:
        process.kill()
    except:
        pass

    process = subprocess.Popen(["python", "simpleaudio_play.py", 
            "songs/" + songs[song_index]])
    return song_index, process

def up_process(volume):
    if volume < 7:
        volume += 1
        os.system("osascript -e 'set Volume %d'" % volume)
    return volume

def down_process(volume):
    if volume > 0:
        volume -= 1
        os.system("osascript -e 'set Volume %d'" % volume)
    return volume

def near_far_process(songs, song_index, process):
    if process.returncode is None:
        process.kill()
    else:
        process = subprocess.Popen(["python", "simpleaudio_play.py", 
                "songs/" + songs[song_index]])
    return song_index, process

if __name__ == '__main__':
    songs = os.listdir("./songs")
    song_index = 0

    volume = 7
    # sa = OSAX()

    arduino = None
    while True:
        try:
            port = "/dev/cu.usbmodem1421"
            arduino = serial.Serial(port, timeout=5)
            break
        except:
            print("Port is wrong")
            time.sleep(2)

    process = subprocess.Popen(["python", "simpleaudio_play.py", 
        "songs/" + songs[song_index]])

    while(1):
        command = str(arduino.readline().decode("utf-8")).rstrip("\r\n")
        print(command)

        if command == "RIGHT":
            song_index, process = right_process(songs, song_index, process)

        if command == "LEFT":
            song_index, process = left_process(songs, song_index, process)

        if command == "UP":
            volume = up_process(volume)

        if command == "DOWN":
            volume = down_process(volume)

        if command == "NEAR" or command == "FAR":
            song_index, process = near_far_process(songs, song_index, process)

        if process.poll() is not None:
            song_index, process = right_process(songs, song_index, process)

