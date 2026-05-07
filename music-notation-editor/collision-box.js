class Collision_Box {
    constructor(x, y, width, height, fill_color, tag = "...") {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
        this.fill_color = fill_color;
        this.tag = tag;
    }
    draw_self(ctx, x_offset = 0, y_offset = 0) {
        ctx.fillStyle = this.fill_color;
        ctx.fillRect(this.x + x_offset, this.y + y_offset, this.width, this.height);
    }
    collision_check(other_box) {
        let x_overlapping = (other_box.x <= this.x && other_box.x + other_box.width >= this.x) || (other_box.x >= this.x && other_box.x <= this.x + this.width);
        let y_overlapping = (other_box.y <= this.y && other_box.y + other_box.height >= this.y) || (other_box.y >= this.y && other_box.y <= this.y + this.height);
        return (x_overlapping && y_overlapping);
    }
    derive_child_box(index, element_limit, fill_color) {
        return new Collision_Box(this.x + ((index * this.width) / element_limit), this.y, this.width / element_limit, this.height, fill_color);
    }
    
    jsonify() {
        return `{ "x":${this.x} , "y":${this.y} , "width":${this.width} , "height":${this.height} , "fill_color":"${this.fill_color}" , "tag":"${this.tag}" }`;
    }
}
