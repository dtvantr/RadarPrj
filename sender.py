import socket
import time
import random
import sys

if len(sys.argv) < 2:
    print("Usage: py sender.py <num_targets>")
    sys.exit(1)

NUM_TARGETS = int(sys.argv[1])

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(("127.0.0.1", 5000))

targets = []

for i in range(NUM_TARGETS):

    targets.append({
        "id": i,
        "x": random.randint(-200, 200),
        "y": random.randint(-200, 200),
        "vx": random.randint(-5, 5),
        "vy": random.randint(-5, 5)
    })

while True:

    lines = []

    for t in targets:

        t["x"] += t["vx"]
        t["y"] += t["vy"]

        if t["x"] > 250 or t["x"] < -250:
            t["vx"] *= -1

        if t["y"] > 250 or t["y"] < -250:
            t["vy"] *= -1

        lines.append(f'{t["id"]} {t["x"]} {t["y"]}')

    msg = "\n".join(lines) +"\n"

    client.sendall(msg.encode())

    print(f"Sent {NUM_TARGETS} targets")

    time.sleep(0.05)