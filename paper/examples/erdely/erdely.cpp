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
#include <cmath>
#include <iostream>
#include <map>
#include <string>

#define CHECK_FLAG(SFLAG, LFLAG, FROM, TO, ARGV) [&]()->int { for (int _i = FROM; _i < TO; ++_i) { if (std::string(ARGV[_i]) == SFLAG || std::string(ARGV[_i]) == LFLAG) return _i; } return 0; }()
#define HAS_FLAG(SFLAG, LFLAG, ARGC, ARGV) CHECK_FLAG(SFLAG, LFLAG, 1, ARGC, ARGV)
#define PARSE_FLAG_VALUE(SFLAG, LFLAG, DEFAULT, FROM, TO, ARGC, ARGV) [&](){ int _j = CHECK_FLAG(SFLAG, LFLAG, FROM, TO, ARGV); return (_j && (++_j) < ARGC) ? ARGV[_j] : DEFAULT; }()
#define PARSE_FLAG(SFLAG, LFLAG, DEFAULT, ARGC, ARGV) PARSE_FLAG_VALUE(SFLAG, LFLAG, DEFAULT, 1, ARGC, ARGC, ARGV);

class SzeklerWriter {
    static constexpr float kPi = 2.0 * std::asin(1.0);
public:
    static const std::string kLower;
    static const std::string kUpper;

    static const std::string toLower(std::string upper)
    {
        std::string lower = upper;
        for (size_t i = 0; i < lower.length(); ++i) {
            const size_t pos = kUpper.find(lower[i]);
            if (pos != std::string::npos) {
                lower[i] = kLower[pos];
            }
        }
        return lower;
    }

    SzeklerWriter(gepard::Gepard& ctx, const float fontSize = 12.0)
        : _ctx(ctx)
        , _fontSize(fontSize)
    {
        _lw = _ctx.lineWidth;
        _leadingSize = _fs * 0.7 * 0.5;
    }

    SzeklerWriter& text(const std::string latin)
    {
        std::string str = toLower(latin);
        while (!str.empty()) {
            size_t adv = 1;

            if (str.find(" x ") == 0) { x(); adv = 3; }
            else if (str.find("ély") == 0) { eely(); adv = 3; }
            else if (str.find("ba") == 0) { ba(); adv = 2; }
            else if (str.find("ly") == 0) { ly(); adv = 2; }
            else if (str.find("rd") == 0) { Rd(); adv = 2; }
            else if (str.find("sz") == 0) { sz(); adv = 2; }
            else if (str.find("a") == 0) { a(); }
            else if (str.find("d") == 0) { d(); }
            else if (str.find("e") == 0) { e(); }
            else if (str.find("é") == 0) { ee(); }
            else if (str.find("r") == 0) { R(); }
            else if (str.find("t") == 0) { t(); }
            else if (str.find(" ") == 0) { _(); }
            else if (str.find("*") == 0) { STAR(); }
            else if (str.find("#") == 0) { KonyaSTAR(); }
            else if (str.find(")") == 0) { MOON(); }

            str.erase(0, adv);
        }

        return *this;
    }

    SzeklerWriter& _()
    {
        begin();
        leading(0.5);
        moveCursor(0.5);
        return flush();
    }

    SzeklerWriter& x()
    {
        begin();
        leading(0.5);
        _ctx.save();

        _ctx.moveTo( 0.07 * _fs, 0.43 * _fs);
        _ctx.lineTo(-0.07 * _fs, 0.57 * _fs);
        _ctx.moveTo(-0.07 * _fs, 0.43 * _fs);
        _ctx.lineTo( 0.07 * _fs, 0.57 * _fs);

        _ctx.restore();
        moveCursor(0.5);
        return flush();
    }

    SzeklerWriter& a()
    {
        begin();
        leading(0.2);
        _ctx.save();

        _ctx.moveTo(0.0 * _fs, 0.0 * _fs);
        _ctx.lineTo(0.0 * _fs, 1.0 * _fs);
        _ctx.moveTo(0.0 * _fs, 0.0 * _fs);
        _ctx.lineTo(-0.25 * _fs, 0.25 * _fs);
        _ctx.lineTo(0.0 * _fs, 0.5 * _fs);

        _ctx.restore();
        moveCursor(0.8);
        return flush();
    }

    SzeklerWriter& ba()
    {
        begin();
        leading(0.7);
        _ctx.save();

        _ctx.moveTo(0.25 * _fs, 0.0 * _fs);
        _ctx.lineTo(-0.25 * _fs, 1.0 * _fs);
        _ctx.moveTo(-0.25 * _fs, 0.0 * _fs);
        _ctx.lineTo(0.25 * _fs, 1.0 * _fs);
        _ctx.moveTo(-0.25 * _fs, 0.0 * _fs);
        _ctx.lineTo(-0.3 * _fs, 0.20 * _fs);
        _ctx.lineTo(-0.1 * _fs, 0.30 * _fs);

        _ctx.restore();
        moveCursor(0.9);
        return flush();
    }

    SzeklerWriter& d()
    {
        begin();
        leading(0.7);
        _ctx.save();

        _ctx.moveTo(0.0 * _fs, 0.0 * _fs);
        _ctx.lineTo(0.0 * _fs, 1.0 * _fs);
        _ctx.moveTo(0.20 * _fs, 0.3 * _fs);
        _ctx.lineTo(-0.20 * _fs, 0.7 * _fs);

        _ctx.restore();
        moveCursor(0.7);
        return flush();
    }

    SzeklerWriter& e()
    {
        begin();
        leading(0.7);
        _ctx.save();

        _ctx.moveTo(-0.1 * _fs, 0.0);
        _ctx.bezierCurveTo(0.15 * _fs, 0.35 * _fs, 0.15 * _fs, 0.65 * _fs, -0.1 * _fs, _fs);
        _ctx.moveTo(0.15 * _fs, 0.08 * _fs);
        _ctx.lineTo(-0.10 * _fs, 0.30 *  _fs);
        _ctx.moveTo(0.15 * _fs, 0.92 * _fs);
        _ctx.lineTo(-0.10 * _fs, 0.70 *  _fs);

        _ctx.restore();
        moveCursor(0.7);
        return flush();
    }

    SzeklerWriter& ee()
    {
        begin();
        leading(0.7);
        _ctx.save();

        _ctx.moveTo(-0.1 * _fs, 0.0);
        _ctx.bezierCurveTo(0.15 * _fs, 0.35 * _fs, 0.15 * _fs, 0.65 * _fs, -0.1 * _fs, _fs);
        _ctx.moveTo(0.2 * _fs, 0.08 * _fs);
        _ctx.lineTo(0.02 * _fs, 0.20 *  _fs);
        _ctx.moveTo(0.2 * _fs, 0.92 * _fs);
        _ctx.lineTo(0.02 * _fs, 0.8 *  _fs);

        _ctx.restore();
        moveCursor(0.7);
        return flush();
    }

    SzeklerWriter& eely()
    {
        begin();
        leading(0.7);
        _ctx.save();

        _ctx.moveTo(0.0 * _fs, 0.0);
        _ctx.bezierCurveTo(0.25 * _fs, 0.35 * _fs, 0.25 * _fs, 0.65 * _fs, 0.0 * _fs, _fs);
        _ctx.moveTo(0.0 * _fs, 0.0);
        _ctx.bezierCurveTo(-0.25 * _fs, 0.35 * _fs, -0.25 * _fs, 0.65 * _fs, 0.0 * _fs, _fs);
        _ctx.moveTo(0.03 * _fs, 0.55 * _fs);
        _ctx.lineTo(-0.16 * _fs, 0.69 *  _fs);
        _ctx.moveTo(0.3 * _fs, 0.08 * _fs);
        _ctx.lineTo(0.12 * _fs, 0.20 *  _fs);
        _ctx.moveTo(0.3 * _fs, 0.92 * _fs);
        _ctx.lineTo(0.12 * _fs, 0.8 *  _fs);

        _ctx.restore();
        moveCursor(0.7);
        return flush();
    }

    SzeklerWriter& ly()
    {
        begin();
        leading(0.7);
        _ctx.save();

        _ctx.moveTo(0.0 * _fs, 0.0);
        _ctx.bezierCurveTo(0.25 * _fs, 0.35 * _fs, 0.25 * _fs, 0.65 * _fs, 0.0 * _fs, _fs);
        _ctx.moveTo(0.0 * _fs, 0.0);
        _ctx.bezierCurveTo(-0.25 * _fs, 0.35 * _fs, -0.25 * _fs, 0.65 * _fs, 0.0 * _fs, _fs);
        _ctx.moveTo(0.03 * _fs, 0.55 * _fs);
        _ctx.lineTo(-0.16 * _fs, 0.69 *  _fs);

        _ctx.restore();
        moveCursor(0.7);
        return flush();
    }

    SzeklerWriter& R()
    {
        begin();
        leading(0.9);
        _ctx.save();

        _ctx.moveTo(0.2 * _fs, 0.0 * _fs);
        _ctx.lineTo(0.2 * _fs, 1.0 * _fs);
        _ctx.moveTo(-0.2 * _fs, 0.0 * _fs);
        _ctx.lineTo(-0.2 * _fs, 1.0 * _fs);
        _ctx.moveTo(0.2 * _fs, 0.40 * _fs);
        _ctx.lineTo(-0.2 * _fs, 0.65 *  _fs);

        _ctx.restore();
        moveCursor(0.9);
        return flush();
    }

    SzeklerWriter& Rd()
    {
        begin();
        leading(1.0);
        _ctx.save();

        _ctx.moveTo(0.3 * _fs, 0.0 * _fs);
        _ctx.lineTo(0.3 * _fs, 1.0 * _fs);
        _ctx.moveTo(-0.10 * _fs, 0.0 * _fs);
        _ctx.lineTo(-0.10 * _fs, 1.0 * _fs);
        _ctx.moveTo(0.3 * _fs, 0.40 * _fs);
        _ctx.lineTo(-0.3 * _fs, 0.65 *  _fs);

        _ctx.restore();
        moveCursor(1.0);
        return flush();
    }

    SzeklerWriter& r()
    {
        begin();
        leading(0.7);
        _ctx.save();

        _ctx.moveTo(0.2 * _fs, 0.40 * _fs);
        _ctx.lineTo(-0.2 * _fs, 0.65 *  _fs);

        _ctx.restore();
        moveCursor(0.7);
        return flush();
    }

    SzeklerWriter& sz()
    {
        begin();
        leading(0.3);
        _ctx.save();

        _ctx.moveTo(0.0 * _fs, 0.0 * _fs);
        _ctx.lineTo(0.0 * _fs, 1.0 * _fs);

        _ctx.restore();
        moveCursor(0.5);
        return flush();
    }

    SzeklerWriter& t()
    {
        begin();
        leading(0.3);
        _ctx.save();

        _ctx.moveTo(0.0 * _fs, 0.0 * _fs);
        _ctx.lineTo(0.0 * _fs, 1.0 * _fs);
        _ctx.moveTo(0.0 * _fs, 0.4 * _fs);
        _ctx.lineTo(-0.3 * _fs, 0.0 * _fs);

        _ctx.restore();
        moveCursor(0.7);
        return flush();
    }

    SzeklerWriter& KonyaSTAR(const float size = 0.8)
    {
        return STAR(true, size);
    }

    SzeklerWriter& STAR(const bool isKonyaStar = false, const float size = 0.8)
    {
        const float kPi8 = kPi / 8.0;

        begin();
        leading(1.5);
        _ctx.save();

        const float s = _fs * size;
        const float _a = 0.5 * s;
        const float _a2 = _a / 2.0;
        const float _b2 = _a2 * std::tan(kPi8);

        _ctx.translate(0.0, 0.5 * _fs);
        for (int i = 0; i < 8; ++i) {
            _ctx.lineTo(0.0, _a);
            _ctx.lineTo(-_b2, _a2);
            _ctx.rotate(kPi / 4.0);
            _ctx.lineTo(_b2, _a2);
        }
        _ctx.closePath();
        if (isKonyaStar) {
            _ctx.rotate(kPi8);
        }
        _ctx.translate(0.0, -0.5 * _fs);

        _ctx.restore();
        _ctx.fill();
        moveCursor(1.5);
        return flush();
    }

    SzeklerWriter& MOON(const float size = 0.8)
    {
        begin();
        leading(1.4);
        _ctx.save();

        const float s = _fs * size;

        _ctx.translate(0.0, 0.5 * _fs);
        _ctx.moveTo(0.5 * s * cos(4.0 / 3.0 * kPi), 0.5 * s * sin(4.0 / 3.0 * kPi));
        _ctx.arc(0.0, 0.0, 0.5 * s, 4.0 / 3.0 * kPi, 2.0 / 3.0 * kPi);
        _ctx.arc(-0.2 * _fs, 0.0, 0.4 * s, 1.5 / 3.0 * kPi, 4.5 / 3.0 * kPi, true);
        _ctx.closePath();
        _ctx.translate(0.0, -0.5 * _fs);

        _ctx.restore();
        _ctx.fill();
        moveCursor(0.4);
        return flush();
    }

    SzeklerWriter& stroke()
    {
        _ctx.stroke();
        return *this;
    }

    SzeklerWriter& fill()
    {
        _ctx.fill();
        return *this;
    }

private:
    void begin()
    {
        _ctx.beginPath();
    }

    SzeklerWriter& flush()
    {
        stroke();
        return *this;
    }

    void moveCursor(const float size = 1.0)
    {
        _ctx.translate(size * _direction * _leadingSize, 0.0);
    }

    void leading(const float size = 1.0)
    {
        moveCursor(size);
    }

    const float _direction = -1.0;

    gepard::Gepard& _ctx;
    float _fontSize;
    float _leadingSize;

    const float& _fs = _fontSize;
    const float& _ls = _leadingSize;
    float _lw;
};

const std::string SzeklerWriter::kLower = "aábcdeéfghiíjklmnoóöőpqrstuúüűvwxyz";
const std::string SzeklerWriter::kUpper = "AÁBCDEÉFGHIÍJKLMNOÓÖŐPQRSTUÚÜŰVWXYZ";

int main(int argc, char* argv[])
{
    if (HAS_FLAG("-h", "--help", argc, argv)) {
        std::cout << "Usage: " << argv[0] << " [output-png]" << std::endl << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -h, --help      show this help." << std::endl;
        return 0;
    }

    const uint width = 2048;
    const uint height = 512;
    gepard::PNGSurface surface(width, height);
    gepard::Gepard ctx(&surface);

    // Clear canvas.
    ctx.fillStyle = "#fff";
    ctx.fillRect(0, 0, width, height);

    ctx.fillStyle = "#b4e256";
    ctx.strokeStyle = "#25385e";
    ctx.lineWidth = 17.0;
    ctx.lineCap = "round";
    ctx.lineJoin = "miter";

    ctx.translate(1800, 120);
    SzeklerWriter szw(ctx, 250);

    szw.text(") Szabad x Erdélyt #");

    std::string pngFile = argc > 1 ? argv[1] : "./paper/src/img/erdely.png";
    surface.save(pngFile);

    return 0;
}
