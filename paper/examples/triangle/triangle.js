<!DOCTYPE html>
<html>
<body>

<canvas id="Canvas" width="1024" height="768">
Your browser does not support the HTML5 canvas tag.
</canvas>

<script>

var cv = document.getElementById("Canvas");
var ctx = cv.getContext("2d");

ctx.fillStyle = "#b4e256";
ctx.strokeStyle = "#25385e";

ctx.translate(50, 50);
ctx.scale(30, 30);

for (var col = 0; col < 3; ++col) {
    for (var row = 0; row < 2; ++row) {
        ctx.save();
        ctx.translate(col * 12, row * 12);

        ctx.beginPath();
        ctx.moveTo(5, 0);
        ctx.lineTo(6, 9);
        ctx.lineTo(0, 3);

        if (row < 1)
            ctx.closePath();  // felső sor
        if (col > 0)
            ctx.fill();  // utolsó két oszlop
        if (col < 2)
            ctx.stroke();  // első két oszlop
        ctx.restore();
    }
}

</script>

</body>
</html>
