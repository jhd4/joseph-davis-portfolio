class bar_staff {
    constructor(x, vertical_offset, width) {
        this.bars = [];
        //normal music staff ranges from g2-f5. We are including one note on either side
        let tags = ["f2", "g2", "a2", "b2", "c3", "d3", "e3", "f3", "g3", "a3", "b3", "c4", "d4", "e4", "f4", "g4", "a4", "b4", "c5", "d5", "e5", "f5", "g5"];
        tags.reverse();
        let current_y = vertical_offset;
        for(let i = 0; i < tags.length; i++) {
            let color = "rgb(255,255,255)";
            let height = 12;
            if(i % 2 === 1) {
                height = 4;
                if(i == 11) {
                    color = "rgb(220,220,220)";
                } else {
                    color = "rgb(0,0,0)";
                }
            }
            this.bars.push(new Collision_Box(x, current_y, width, height, color, tags[i]));
            current_y += height;
        }
        this.box = new Collision_Box(x, vertical_offset, width, current_y - vertical_offset, "rgb(255, 0, 0)");
        this.measures = [];
        let measure_count = 4;
        for(let i = 0; i < measure_count; i++) {
            let collision_box = this.box.derive_child_box(i, measure_count, "rgba(2, 130, 2, 1)");
            this.measures.push(new Measure(collision_box));
        }
    }

    draw_self(ctx) {
        for(let i = 0; i < this.bars.length; i++) {
            this.bars[i].draw_self(ctx);
        }
        for(let i = 0; i < this.measures.length; i++) {
            this.measures[i].draw_self(ctx, this.bars);
        }
    }

    jsonify() {
        let output = `{ "measures": [ `;
        for(let i = 0; i < this.measures.length; i++) {
            output += this.measures[i].jsonify(i);
            if(i + 1 < this.measures.length) {
                output += ",\n";
            }
        }
        output += " ] }";
        return output;
    }
}