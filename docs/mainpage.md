# LARS: Light-Augmented Reality System for Collective Robotics Interaction 🚦🤖

> **📚 Documentation**  
> Developer & API Docs: [`docs/doxygen/html/index.html`](docs/doxygen/html/index.html)

---

![Tracking Example](docs/media/ARK_to_LARS.gif)

---

## ✨ What is LARS?

**LARS** (Light Augmented Reality System) is an open-source, cross-platform framework for *experimentation, education, and outreach* in collective robotics.

- 🚨 **Real-time Augmented Reality:** Projects gradients, fields, trails, and robot states *directly* onto real-world robot arenas.
- 👀 **Invisible → Visible:** Makes collective dynamics tangible for researchers, students, and the public.
- 🔬 **No Hardware Mods:** Works with existing robots—no tags or changes needed!

---

## 🚀 Key Features

| 🛠️ Feature             | 💡 Description                                                                 |
|------------------------|-------------------------------------------------------------------------------|
| **Real-time XR**       | Dynamic overlays and projections, synchronized with real robots                |
| **Marker-free Tracking** | Fast (38+ FPS), robust tracking for 100+ robots, no tags required           |
| **Multi-platform**     | Supports Kilobot, Thymio, E-puck, & more                                      |
| **Open-source**        | Free for research, teaching, and engagement                                   |
| **Low-cost**           | Uses affordable, off-the-shelf components                                     |
| **Reproducible**       | Full data logging & video recording                                           |
| **Flexible**           | Easy to configure and extend                                                  |
| **User-friendly GUI**  | Intuitive Qt-based interface                                                  |

---

## 🎯 Why LARS?

- **For Research:**  
  🧪 Bridge the *sim-to-real* gap. Run reproducible, scalable, and dynamic experiments—preserving robot constraints.

- **For Education:**  
  📚 Transform abstract swarms into interactive, hands-on learning. Perfect for classrooms.

- **For Outreach:**  
  🌟 Demo swarm intelligence live—LARS brings robot collectives to life for everyone.

---

## 👁️‍🗨️ Advanced Tracking & Visual Augmentation

LARS uses a powerful, real-time tracker based on **ARK** (Automatic Robot Kinematics) but goes much further:

- ⚡ **Tracks 100+ robots in real time**
- 🔎 Robust to occlusions, lighting, and noise
- 🔵 Generalizes to any “circular” robot (Kilobot, Thymio, E-puck, more)
- 🏷️ *No tags or hardware mods!*
- 🧠 Auto-preserves & recovers identities—even during close encounters

**Beyond tracking:**  
LARS uniquely projects **virtual visual objects**—gradients, cues, interactive signals—onto the arena *and* atop robots.

- 🌀 Simulate virtual environments and signals without hardware changes
- 🛰️ Provide dynamic, spatial feedback to robots and collectives
- 🕹️ Explore new human-swarm and robot-environment interaction

---

## 🏗️ Architecture Overview

LARS is built on the classic **Model-View-Controller (MVC)** pattern:

- 🧩 **Model:** World state, physics, and objects  
- 🖼️ **View:** GUI, visualization, and projector output  
- 🎮 **Controller:** Experiment orchestration, tracking, and logic

<img src="docs/media/LARS_Diagram.png" alt="LARS MVC Architecture" height="320px">

---

## 🧑‍🔬 Example Scenarios

- 🗳️ **Collective Decision-Making:** Track & visualize 100+ Kilobots in a noisy, projected environment
- ⏰ **Swarm Synchronization:** Record robot states and group dynamics in real time
- 🕹️ **Interactive Demos:** Let visitors steer/interact with swarms and see collective behavior
- 🧑‍🏫 **Educational Labs:** Manipulate real experiments to teach robotics, physics, and complexity

<p align="center">
  <img src="docs/media/kilobot_sync.png" height="140px" alt="(a)">
  <img src="docs/media/kilobot_DM.png" height="140px" alt="(b)">
  <img src="docs/media/kilobot_109.png" height="140px" alt="(c)">
  <img src="docs/media/weazle_balls.png" height="140px" alt="(d)">
</p>
<p align="center" style="font-size: 13px;">
  (a) Kilobots synchronizing &nbsp;
  (b) Collective decision &nbsp;
  (c) 109 Kilobots snapshot &nbsp;
  (d) Active Weazle balls
</p>
<p align="center">
  <img src="docs/media/thymios_PT.png" height="150px" alt="(e)">
  <img src="docs/media/themios_RW.png" height="150px" alt="(f)">
</p>
<p align="center" style="font-size: 13px;">
  (e) Thymios doing phototaxis &nbsp;&nbsp;
  (f) Thymios random walk
</p>

---

## 🚦 Quick Start

**Runs as a Qt application. Ubuntu preferred. See [install_dep.md](install_dep.md) for details.**

```bash
git clone https://github.com/mohsen-raoufi/LARS.git
cd LARS
# Install dependencies (see install_dep.md)
# Build with Qt Creator (recommended) or use qmake + make
```

**User Permissions:**  
Add yourself to the `dialout` group for Kilobot OHC access:
```bash
sudo usermod -a -G dialout <user-name>
```

---

## 📄 Citation

If you use or adapt LARS in your research, please cite:

- Reina A., Cope A.J., Nikolaidis E., Marshall J.A.R., Sabo C. (2017) ARK: Augmented reality for Kilobots. *IEEE Robotics and Automation Letters* **2, 1755-1761**.
- Raoufi, M., Romanczuk, P., & Hamann, H. (2024). *LARS: Light Augmented Reality System for Swarm*. In Swarm Intelligence: 14th International Conference, ANTS 2024, Konstanz, Germany, October 9–11, 2024, Proceedings (Vol. 14987, p. 246). Springer Nature.

---

## 🔗 See Also

- [Kilobot Wiki](http://diode.group.shef.ac.uk/kilobots/index.php/Kilobots)
- API Docs: [`docs/doxygen/html/index.html`](docs/doxygen/html/index.html)

---

LARS is supported by the *Science of Intelligence* Cluster of Excellence, Berlin.  
Developed and maintained by Mohsen Raoufi et al.  
Open-source under the GNU GPL v3.0.

---

🙌 **Contributions welcome! LARS is for scientists, educators, and all who are curious about collective intelligence in robotics.**

---
