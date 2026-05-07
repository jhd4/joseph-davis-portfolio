class Note_Instance {
    constructor(tag, duration) {
        this.tag = tag;
        this.duration = duration;
        this.line_direction = (["d3", "c4","b4", "c5", "d5", "e5", "f5", "g5"].includes(this.tag)) ? 1 : -1; //points down (-1) if it is in the list, up (1) otherwise
    }

    draw_self(ctx, moment_reference, bars_reference) {
        ctx.fillStyle = "rgb(0,0,0)";
        let target_bar = bars_reference[0];
        for(let i = 0; i < bars_reference.length; i++) {
            if(bars_reference[i].tag == this.tag) {
                target_bar = bars_reference[i];
                break;
            }
        }
        let note_x = moment_reference.x + moment_reference.width/2;
        let note_y = target_bar.y + target_bar.height/2;
        let note_x_radius = 8;
        let note_y_radius = 6;
        let note_line_x = note_x - this.line_direction * note_x_radius;
        let note_line_width = 2;
        let note_line_height = 25 * this.line_direction;
        let dot_radius = 3;
        let dot_x = note_x + note_x_radius * 1.7;
        switch(this.duration) {
            case 0.25://16th note
                break;
            case 0.5://8th note
                break;
            case 1.5://dotted quarter note
                elipse(ctx, dot_x, note_y, dot_radius, dot_radius);
            case 1://quarter note
                elipse(ctx, note_x, note_y, note_x_radius, note_y_radius);
                ctx.fillRect(note_line_x, note_y, note_line_width, note_line_height);
                break;            
            case 3://dotted half note
                elipse(ctx, dot_x, note_y, dot_radius, dot_radius);
            case 2://half note
                ctx.fillRect(note_line_x, note_y, note_line_width, note_line_height);
            case 4:
                elipse(ctx, note_x, note_y, note_x_radius, note_y_radius, false);
                break;
        }
    }
    
    jsonify() {
        return `{ "tag":"${this.tag}" , "duration":${this.duration}}`;
    }
}