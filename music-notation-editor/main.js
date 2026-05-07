
let canvas = undefined
let ctx = undefined
let staff_list = [];
let mode_selector = undefined;
let duration_selector = undefined;

function draw_staff_list(ctx, staff_list) {
    for(let i = 0; i < staff_list.length; i++) {
        staff_list[i].draw_self(ctx);
    }
}

window.addEventListener("load", () => {
    //accessing and formatting canvas
    canvas = document.getElementById("music_sheet");
    ctx = canvas.getContext("2d");
    canvas.width = window.innerWidth * 5/6;
    canvas.height = window.innerHeight * 2.3;
    mode_selector = document.getElementById("mode");
    duration_selector = document.getElementById("duration");
    let margin = 20;
    let header_spacing = 50;
    //creating collsion boxes for bar staffs
    staff_list.push(new bar_staff(margin, header_spacing, canvas.width - (2 * margin)));
    let staff_spacing = 40
    for(let i = 0; i < 5; i++) {
        staff_list.push(new bar_staff(margin, staff_list[i].box.y + staff_list[i].box.height + staff_spacing, canvas.width - (2 * margin)));
    }
    draw_canvas();
    //dealing with making notes
    window.addEventListener("mousedown", (event) => {
        let mouse_coords = get_mouse_coords_relative_to_canvas(event.clientX, event.clientY);
        let mouse_box = new Collision_Box(mouse_coords.x, mouse_coords.y, 1, 1, "rgb(0,0,0)", "mouse");
        let note_tag = "c4";//default note name, to avoid using a null
        let duration = parseFloat(duration_selector.value);
        for(let i = 0; i < staff_list.length; i++) {//determine which bar staff it lives in, if any
            let bar_staff = staff_list[i];
            if(mouse_box.collision_check(bar_staff.box)) {//determine which note it is
                for(let j = 0; j < bar_staff.bars.length; j++) {
                    let bar = bar_staff.bars[j];
                    if(mouse_box.collision_check(bar)) {
                        note_tag = bar.tag;
                        break;
                    }
                }
                for(let j = 0; j < bar_staff.measures.length; j++) {//determine horizontal position
                    let measure = bar_staff.measures[j];
                    if(mouse_box.collision_check(measure.collision_box)) {
                        for(let k = 0; k < measure.moments.length; k++) {
                            let moment = measure.moments[k];
                            if(mouse_box.collision_check(moment.collision_box)) {
                                if(mode_selector.value == "insert") {
                                    moment.insert_note_instance(new Note_Instance(note_tag, duration));
                                } else if(mode_selector.value == "remove") {
                                    moment.remove_note_instance(note_tag);
                                }
                                draw_canvas(event);
                                return;
                            }
                        }
                    }
                }
            }
            
        }
    });

    document.getElementById("save_file").addEventListener("mousedown", (event) => {
        ///Downloads a json file of the current composition upon clicking
        //This code was largely take from ChatGPT, as I have not done anything with file downloading before
        const composition_data = jsonify_staff_list(staff_list);
        const blob = new Blob([composition_data], { type: "application/json" });
        const url = URL.createObjectURL(blob);
        const a = document.createElement("a");
        a.href = url;
        a.download = "composition.json";
        a.click();
        URL.revokeObjectURL(url);
    });

    document.getElementById("upload_file").addEventListener("mousedown", (event) => {
        //this function was taken from ChatGPT, since I have no familiarity with uploading files in html
        document.getElementById("fileInput").click();//fires a different event that will allow selection of a file to upload
    });

    document.getElementById("fileInput").addEventListener("change", async (event) => {
        //this function was taken from ChatGPT, since I have no familiarity with uploading files in html
        const file = event.target.files[0];
        if (!file) return;

        const text = await file.text();
        try {
            const data = JSON.parse(text);
            let new_staffs = data.bar_staffs;
            let old_staffs = staff_list;
            for(let i = 0; i < new_staffs.length && i < old_staffs.length; i++) {//iterate through the list of bar staffs
                let new_measures = new_staffs[i].measures;
                let old_measures = old_staffs[i].measures;
                for(let j = 0; j < new_measures.length && j < old_measures.length; j++) { //iterate through the list of measures
                    let new_moments = new_measures[j].moments;
                    let old_moments = old_measures[j].moments;
                    for(let k = 0; k < new_moments.length && k < old_moments.length; k++) {//iterate through the list of moments
                        let new_notes = new_moments[k].note_list;
                        let old_notes = old_moments[k].note_list;
                        while(old_notes.length > 0) {//clear the existing notes, make space for new
                            old_notes.pop();
                        }
                        for(let l = 0; l < new_notes.length; l++) {//add each note from the upload
                            new_note = new_notes[l];
                            old_notes.push(new Note_Instance(new_note.tag, new_note.duration));
                        } 
                    } 
                }
            }
            draw_canvas();
        } catch (err) {
            console.error("Not valid JSON");
        }
    });
});

function jsonify_staff_list(staff_list) {
    //takes the list of bar staffs and converts their contents into a json string
    let output = `{ "bar_staffs": [ `;
        for(let i = 0; i < staff_list.length; i++) {
            output += staff_list[i].jsonify();
            if(i + 1 < staff_list.length) {
                output += ",\n";
            }
        }
        output += " ] }";
        return output;
}

function get_mouse_coords_relative_to_canvas(mouseX, mouseY) {
    //accounts for difference between the event coordinates and the coordinates relative to the canvasd
    let rect = canvas.getBoundingClientRect();
    return {
        x: mouseX - rect.left,
        y: mouseY - rect.top
    };
}

function import_staff_list() {
    return staff_list;
}

function draw_canvas() {
    if (ctx !== undefined && canvas !== undefined) {
        ctx.fillStyle = "rgb(255, 255, 255)"
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        draw_staff_list(ctx, staff_list);
    }
}

function elipse(ctx, x, y, x_radius, y_radius, fill=true) {
    //takes care of repeat code with drawing elipses
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.ellipse(x, y, x_radius, y_radius, 0, 0, 2 * Math.PI);
    if(fill) {
        ctx.fill();
    } else {
        ctx.stroke();
    }
}

