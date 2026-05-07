class Moment {
    constructor(collision_box, note_list = []) {
        this.collision_box = collision_box;
        this.note_list = note_list;
    }

    contains_note_instance(tag) {
        for(let i = 0; i < this.note_list.length; i++) {
            if(this.note_list[i].tag == tag) {
                return true;
            }
        }
        return false;
    }

    insert_note_instance(note_instance) {
        if(!this.contains_note_instance(note_instance.tag)) {
            this.note_list.push(note_instance);
        }
    }

    draw_self(ctx, bars_reference) {
        if(this.note_list.length > 0) {
            for(let i = 0; i < this.note_list.length; i++) {
                this.note_list[i].draw_self(ctx, this.collision_box, bars_reference);
            }
        } else {

        }
        
    }

    remove_note_instance(tag) {
        for(let i = this.note_list.length - 1; i >= 0; i--) {//iterating backwards, to avoid messiness with changing indices part way with element removal
            if(this.note_list[i].tag == tag) {
                this.note_list.splice(i, 1);
            }
        }
    }

    jsonify() {
        let output = `{ "note_list": [ `;
        for(let i = 0; i < this.note_list.length; i++) {
            output += this.note_list[i].jsonify();
            if(i + 1 < this.note_list.length) {
                output += ",\n";
            }
        }
        output += " ] }";
        return output;
    }
}