# Interactive JavaScript Music Notation Editor

A web-based, object-oriented music editor that allows users to visually compose, play, and save musical scores. This project utilizes a custom collision-detection engine and the **Tone.js** library to bridge visual interaction with real-time audio synthesis.

### 🎼 Key Technical Features
* **Hierarchical Object Architecture:** Managed complex state through a nested data model: `BarStaff` → `MusicMeasure` → `MusicMoment` → `NoteInstance`.
* **Custom Collision Engine:** Developed a `Collision_Box` utility class to handle coordinate mapping between mouse events and musical staff locations, covering a pitch range from G2 to G5.
* **Dynamic Audio Scheduling:** Integrated **Tone.js PolySynth** to schedule and trigger asynchronous audio events based on a variable-duration note list.
* **Data Persistence:** Implemented custom `jsonify()` methods across all classes to allow for local file saving and state restoration via JSON serialization.

---

### 📂 File Structure & Logic
* **`index.html`**: The UI layer integrating audio context triggers and user controls.
* **`main.js`**: Core event loop handling coordinate translation, note placement, and state management.
* **`collision-box.js`**: The foundational geometry engine for spatial interaction and collision detection.
* **`bar-staff.js`**: Generates the visual staff layout and manages the collection of musical measures.
* **`music-measure.js`**: Manages the rhythmic grid (moments) within a specific section of the staff.
* **`music-moment.js`**: A temporal unit that acts as a container for notes occurring at the same timestamp.
* **`note-instance.js`**: Handles the procedural drawing of musical symbols (stems, dots, ellipses) and stores duration data.

---

### 🚀 Usage
1.  Open `index.html` in any modern web browser.
2.  Select **Mode** (Insert/Remove) and **Note Duration** from the interface.
3.  Click the staff to place notes; the system automatically calculates the pitch (tag) and timing (moment) based on the mouse coordinates.
4.  Click **Play** to synthesize the composition using the Web Audio API.
5.  Click **Save File** to export the current composition as a `.json` score.

### 🛠 Tech Stack
* **Language:** JavaScript (ES6+)
* **Libraries:** Tone.js (Web Audio API)
* **Graphics:** HTML5 Canvas API