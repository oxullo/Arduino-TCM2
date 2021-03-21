#!/usr/bin/env python
# -*- coding: utf-8 -*-

# TCM2lib - MPico TCS gen2 E-ink arduino driver
# Copyright (C) 2016  OXullo Intersecans <x@brainrapers.org>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

'''
This tool converts any image source into an EPD format data type 0 header file,
for the TCM2-P441 combo (4,41", 400x300px).

In order to achieve maximum image quality, provide an image with the required
resolution (400x300), 1-bit bilevel mode.
Pixels alignment if using a vector-based image editor is crucial to avoid jagged
strokes.

Usage:

    $ ./epd_convert.py <input file> <output file>

Example:

    $ ./epd_convert.py test-image.png test_image.h
'''

from __future__ import print_function

import sys
import os
import argparse
import logging

logger = logging.getLogger(__name__)

def fail(msg):
    logger.error(msg)
    sys.exit(1)

try:
    from PIL import Image
except ImportError:
    fail('the required PIL library is missing')

EPD_HEADER = [0x33, 0x01, 0x90, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
              0x00, 0x00, 0x00, 0x00]
HFILE_TEMPLATE = '''// Generated with epd_convert.py
// Original file: %(file)s

#include <avr/pgmspace.h>

#define TOTAL_SIZE      15000+16

const unsigned char test_1bit[TOTAL_SIZE] PROGMEM = {
%(data)s
};
'''
BYTES_PER_LINE = 20

def convert(im, epd_format):
    if not epd_format == 0 and not epd_format == 2:
        raise ValueError('EPD format type {} not implemented'.format(epd_format))

    assert im.size == (400, 300)
    assert im.mode == '1'

    data = EPD_HEADER[:]

    # Set pixel data format in header
    data[6] = epd_format

    # EPD pixel data format type 0 and 2
    for stride in xrange(im.size[0] * im.size[1] / 8):
        x = (stride * 8) % im.size[0]
        y = (stride * 8) / im.size[0]

        val = 0

# Data format type 2
# Input byte 0: assign to output byte bit 0
# Input byte 1: assign to output byte bit 2
# Input byte 2: assign to output byte bit 4
# Input byte 3: assign to output byte bit 6
# Input byte 4: assign to output byte bit 1
# Input byte 5: assign to output byte bit 3
# Input byte 6: assign to output byte bit 5
# Input byte 7: assign to output byte bit 7

        # for type 2
        trans = [0, 2, 4, 6, 1, 3, 5, 7]

        for offs in xrange(8):
            if im.getpixel((x + offs, y)) == 0:
                if epd_format == 0:
                    val |= 1 << (7 - offs)
                elif epd_format == 2:
                    val |= 1 << (7 - trans[offs])

        data.append(val)

    return data

def format_data(data):
    lines = [', '.join(['0x%02X' % byte for byte in data[i:i+BYTES_PER_LINE]])
             for i in xrange(0, len(data), BYTES_PER_LINE)]

    lines = ['    %s,' % line for line in lines[:-1]] + ['    %s' % lines[-1]]
    lines = '\n'.join(lines)

    return lines

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('infile', help='Input file (any graphic type is supported)')
    parser.add_argument('outfile', help='Output file (header file)')
    parser.add_argument('--type', '-t', choices=['cheader', 'binary'], default='cheader',
                        help='Output type')
    parser.add_argument('--epdformat', '-e', choices=['0', '2', '4'], default='0',
                        help='EPD format type')

    return parser.parse_args()

def run():
    logging.basicConfig(level=logging.INFO, format='[%(levelname)10s]: %(message)s')
    args = parse_args()

    if not os.path.exists(args.infile):
        fail('%s: no such file' % args.infile)

    input_image = Image.open(args.infile)

    logger.info('input file=%s size=%s format=%s epd_format=%s mode=%s' % (args.infile, input_image.size,
                                                        input_image.format, args.epdformat, input_image.mode))
    if input_image.size != (400, 300):
        logger.warning('the input image will be scaled to 400x300')
        input_image = input_image.resize((400, 300))

    if input_image.format != '1':
        logger.warning('the input image mode will be converted to bitmap')
        input_image = input_image.convert('1')

    data = convert(input_image, int(args.epdformat))

    logger.info('Output type: %s' % args.type)
    if args.type == 'cheader':
        context = {'file': args.infile, 'data': format_data(data)}

        fout = open(args.outfile, 'w')
        fout.write(HFILE_TEMPLATE % context)
        fout.close()
    else:
        fout = open(args.outfile, 'wb')
        fout.write(''.join([chr(c) for c in data]))
        fout.close()

    logger.info('conversion terminated')


if __name__ == '__main__':
    run()
