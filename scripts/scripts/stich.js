var sel = getMatching({type: "path", selected: true});
if (sel.length > 0) {
    values = prompt("Stich:",
        {type: "number", value: 1, title: "distance", width: 50},
        {type: "number", value: 10, title: "size", width: 50}
    );
    for (var j = 0; j < sel.length; j++) {
        var obj = sel[j];
        var dist = values[0];
        var size = values[1];
        obj = obj.clone();
        obj.curvesToPoints(dist, 100000);
        var count = obj.beziers.length;
        var mul = 1;
        var res = new Art("path");
        for (var i = 0; i < count; i++) {
            var bezier = obj.beziers[i];
            var pt = bezier.getPoint(0);
            var n = bezier.getNormal(0).normalize(size);

            res.segments.push(pt.add(n.mul(mul)));
            pos += dist;
            mul *= -1;
        }
        obj.remove();
    }
}