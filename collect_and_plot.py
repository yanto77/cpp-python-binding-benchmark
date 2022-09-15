#!/usr/bin/env python3
from pprint import pprint
from subprocess import Popen, PIPE, CalledProcessError
from math import ceil
import matplotlib.pyplot as plt
import os

RUN_TIMES = 5

def run_cmd(cmd):
    output = []
    with Popen(cmd, stdout=PIPE, bufsize=1, universal_newlines=True) as p:
        for line in p.stdout:
            print(line, end='')
            output.append(line)

    if p.returncode != 0:
        raise CalledProcessError(p.returncode, p.args)

    return ''.join(output)

def print_header(msg):
    print('=======================')
    print('')
    print(msg)
    print('')
    print('=======================')


def main():
    # 1. Prepare
    if not os.path.exists('./notes/results'):
        os.makedirs('./notes/results')

    # 2. Build once
    print_header('Building benchmark ...')
    run_cmd(['/usr/bin/bash', 'build.sh'])

    # 3. Run benchmark multiple times
    output = ""
    for i in range(RUN_TIMES):
        print_header(f'Run {i+1}/{RUN_TIMES} ...')
        output += run_cmd(['/usr/bin/bash', 'benchmark.sh'])

    # 4. Parse output data into a structure
    data = {} # dict(test, dict(variant, dict(module, [numbers])))
    for line in output.splitlines():
        datapoint = line.split(",")
        if len(datapoint) != 4:
            print("ERR: unexpected format, cannot parse")
            continue

        test = datapoint[0].strip()
        variant = datapoint[1].strip()
        module = datapoint[2].strip()
        time = float(datapoint[3].replace('sec', '').strip())

        if not (test in data.keys()):
            data[test] = {}

        if not (variant in data[test].keys()):
            data[test][variant] = {}

        if not (module in data[test][variant].keys()):
            data[test][variant][module] = []
        
        data[test][variant][module].append(time)

    # 5. Save intermediate output to a file for safe-keeping
    with open("notes/results/output-data.log", "w") as f:
        f.write('== Output:\n\n')
        f.write(f"{output}\n")

        f.write('== Data:\n\n')
        pprint(data, f)

    # 6. Create plots
    for test in data.keys():
        ymax = 0
        for variant in data[test].keys():
            values = [data[test][variant][module] for module in data[test][variant]]
            means = [sum(val) / len(val) for val in values]
            ymax = max(ymax, max(means))

        ymax = ceil(ymax)

        for variant in data[test].keys():
            fig = plt.figure(figsize = (8, 5))

            modules = data[test][variant].keys()
            values = [data[test][variant][module] for module in data[test][variant]]
            means = [sum(val) / len(val) for val in values]

            plt.bar(modules, means)
            plt.title(f'{test}-{variant}')
            plt.ylabel('time [sec]')

            ax = plt.gca()
            ax.set_ylim([0, ymax])
            ax.set_axisbelow(True)
            ax.yaxis.grid(color='gray', linestyle='dashed')

            plt.xticks(rotation = 45)
            plt.tight_layout()
            plt.savefig(f'notes/results/{test}-{variant}-result.png')


if __name__ == "__main__":
    main()