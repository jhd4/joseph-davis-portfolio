class Measure {
    constructor(collision_box) {
        this.collision_box = collision_box;
        this.moments = [];
        let moment_count = 8;
        for(let i = 0; i < moment_count; i++) {
            let collision_box = this.collision_box.derive_child_box(i, moment_count, "rgb(0,255,0)");
            new Collision_Box(this.collision_box.x + ((i * this.collision_box.width) / moment_count), this.collision_box.y, this.collision_box.width / moment_count, this.collision_box.height, "rgb(0,255,0)");
            this.moments.push(new Moment(collision_box));
        }
    }

    draw_self(ctx, bars_reference) {
        // this.collision_box.draw_self(ctx);
        ctx.fillStyle = "rgb(0,0,0)";
        let measure_bar_width = 3;
        let vertical_buffer = bars_reference[0].height;
        ctx.fillRect(this.collision_box.x, this.collision_box.y + vertical_buffer, measure_bar_width, this.collision_box.height - vertical_buffer * 2);
        ctx.fillRect(this.collision_box.x + this.collision_box.width, this.collision_box.y + vertical_buffer, measure_bar_width, this.collision_box.height - vertical_buffer * 2);
        for(let i = 0; i < this.moments.length; i++) {
            this.moments[i].draw_self(ctx, bars_reference);
        }
    }

    jsonify() {
        let output = `{ "moments": [ `;
        for(let i = 0; i < this.moments.length; i++) {
            output += this.moments[i].jsonify();
            if(i + 1 < this.moments.length) {
                output += ",\n";
            }
        }
        output += " ] }";
        return output;
    }
}