# LARS

**Light-Augmented Reality System for Collective Robotics Interaction**

---

> **📚 Documentation**  
> Developer & API Docs: [`docs/doxygen/html/index.html`](docs/doxygen/html/index.html)

---

LARS (**L**ight-**A**ugmented **R**eality **S**ystem) is an advanced, open-source platform designed to transform experimentation and research in collective robotics, swarm intelligence, and distributed artificial systems. Leveraging real-time **augmented reality** techniques, LARS seamlessly blends virtual projections, robust tracking, and live feedback with real-world robot collectives — enabling experiments that were previously impossible or tedious to realize.

## What is LARS?

LARS enables you to **project virtual objects, light fields, gradients, and feedback directly onto a swarm of physical robots** (e.g., Kilobots, Thymio, e-puck, and more) without hardware modifications. The system provides:

- **Real-Time Tracking:** Ultra-fast, general-purpose multi-robot tracking based on an enhanced version of ARK (Automatic Robot Kinematics), supporting 100+ robots at >35 FPS, robust to occlusions and lighting changes.
- **Augmented Reality Feedback:** Dynamically project patterns, light cues, spatial gradients, or even interactive fields that influence robot behaviors — all programmable and spatially aligned to the robots’ real positions.
- **Scalable & Flexible:** LARS works out-of-the-box with various robot types and supports large-scale, high-density experiments.
- **Open, Modular Architecture:** Built in C++/Qt, with an extensible codebase and GUI for configuration, visualization, and experiment control.
- **Educational & Outreach Ready:** LARS has been used in research, teaching, and public science communication.

## Key Features

- **Augmented Reality Projection:** Overlay dynamic visual stimuli (light, color, virtual objects) precisely onto robot arenas to guide, challenge, or observe robots in closed-loop experiments.
- **Next-Generation Tracking:** Generalizes and optimizes the ARK approach to robustly track any robot with a roughly circular appearance from above—no tags or hardware changes required.
- **Data Logging & Analysis:** All experimental data can be logged for later analysis, with options for position, velocity, and robot state tracking.
- **Rich GUI:** Interactive Qt-based interface for setup, live monitoring, and experiment control.
- **Highly Extensible:** Ready to adapt for new robot platforms, sensing, or projection methods.

---

## Quick Start

LARS runs as a Qt application (Qt 5.6+ recommended). Ubuntu is the preferred OS for development and deployment. See our [install_dep.md](https://github.com/mohsen-raoufi/LARS/blob/main/install_dep.md) for details on all required dependencies (CUDA/OpenCV3, Qt, etc.).

1. **Clone the repo:**  
   ```bash
   git clone https://github.com/mohsen-raoufi/LARS.git
   cd LARS
   ```

2. **Install dependencies:**  
   - Qt 5.6+ ([Download](https://www.qt.io))
   - CUDA-supporting OpenCV 3 ([Install guide](https://gist.github.com/filitchp/5645d5eebfefe374218fa2cbf89189aa))
   - See [install_dep.md](https://github.com/mohsen-raoufi/LARS/blob/main/install_dep.md) for details.

3. **Build with Qt Creator** (recommended) or manually with `qmake` and `make`.

4. **User Permissions:**  
   Add yourself to the `dialout` group for Kilobot OHC access:
   ```bash
   sudo usermod -a -G dialout <user-name>
   ```

---

## Applications

- **Collective Robotics Research:** Run closed-loop, spatially explicit experiments with heterogenous swarms.
- **Education & Outreach:** Bring interactive, visually striking robotics demos to classrooms and public events.
- **General Multi-Agent Systems:** Use LARS as a testbed for distributed computation, coordination, and collective decision-making.

---

## Citation

If you use or adapt LARS in your research, please cite:

[1] Reina A., Cope A.J., Nikolaidis E., Marshall J.A.R., Sabo C. (2017) ARK: Augmented reality for Kilobots. *IEEE Robotics and Automation Letters* **2, 1755-1761**.

[2] Raoufi, M., Romanczuk, P., & Hamann, H. (2024). LARS: Light Augmented Reality System for Swarm. In Swarm Intelligence: 14th International Conference, ANTS 2024, Konstanz, Germany, October 9–11, 2024, Proceedings (Vol. 14987, p. 246). Springer Nature.

---

## See Also

- [Kilobot Wiki](http://diode.group.shef.ac.uk/kilobots/index.php/Kilobots)

---

_Developed and maintained by Mohsen Raoufi et al. Inspired by and extending the ARK and DiODe systems. Contributions welcome!_
