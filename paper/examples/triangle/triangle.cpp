/* Copyright (C) 2018, Gepard Graphics
 * Copyright (C) 2018, Szilard Ledan <szledan@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "gepard.h"
#include "surfaces/gepard-png-surface.h"
#include <iostream>
#include <string>

#define CHECK_FLAG(SFLAG, LFLAG, FROM, TO, ARGV) [&]()->int { for (int _i = FROM; _i < TO; ++_i) { if (std::string(ARGV[_i]) == SFLAG || std::string(ARGV[_i]) == LFLAG) return _i; } return 0; }()
#define HAS_FLAG(SFLAG, LFLAG, ARGC, ARGV) CHECK_FLAG(SFLAG, LFLAG, 1, ARGC, ARGV)
#define PARSE_FLAG_VALUE(SFLAG, LFLAG, DEFAULT, FROM, TO, ARGC, ARGV) [&](){ int _j = CHECK_FLAG(SFLAG, LFLAG, FROM, TO, ARGV); return (_j && (++_j) < ARGC) ? ARGV[_j] : DEFAULT; }()
#define PARSE_FLAG(SFLAG, LFLAG, DEFAULT, ARGC, ARGV) PARSE_FLAG_VALUE(SFLAG, LFLAG, DEFAULT, 1, ARGC, ARGC, ARGV);

int main(int argc, char* argv[])
{
    if (HAS_FLAG("-h", "--help", argc, argv)) {
        std::cout << "Usage: " << argv[0] << " [output-png]" << std::endl << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -h, --help      show this help." << std::endl;
        return 0;
    }

    const uint width = 1024;
    const uint height = 768;

    gepard::PNGSurface surface(width, height);
    gepard::Gepard ctx(&surface);

    ctx.fillStyle = "#fff";
    ctx.fillRect(0, 0, width, height);

    ctx.fillStyle = "#b4e256";
    ctx.strokeStyle = "#25385e";

    ctx.translate(50, 50);
    ctx.scale(30, 30);

    for (int col = 0; col < 3; ++col) {
        for (int row = 0; row < 2; ++row) {
            ctx.save();
            ctx.translate(col * 12, row * 12);

            ctx.beginPath();
            ctx.moveTo(5, 0);
            ctx.lineTo(6, 9);
            ctx.lineTo(0, 3);

            if (row < 1) {
                ctx.closePath();
            }
            if (col > 0) {
                ctx.fill();
            }
            if (col < 2) {
                ctx.stroke();
            }
            ctx.restore();
        }
    }

    std::string pngFile = argc > 1 ? argv[1] : "./paper/src/img/triangle.png";
    surface.save(pngFile);

    return 0;
}
