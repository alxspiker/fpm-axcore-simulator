# FPM AxCore Emergent Lattice Simulator

Finite Possibility Mechanics, rendered as a deterministic C++ substrate.

This repository contains a self-contained AxCore simulator that builds a flat `Z^3` daemon arena, advances daemon events through an integer-time radix heap, and measures observables as route-cost outcomes of the ledger. The companion Python tooling is deliberately kept outside the engine: it compiles/runs the substrate, plots artifacts, parses external SPARC data, and feeds the C++ binary only small sanitized IPC payloads.

## Current Status

The engine currently passes the full architectural harness:

```powershell
python .\test_axcore_engine.py
```

Latest result:

```text
38 checks, 0 failures
```

The test harness verifies:

- clean compile and deterministic simulator execution
- bit-for-bit identical JSON across two runs
- exact `N_bit_eq = 1,452,997,909`
- radix heap scheduler present, `std::priority_queue` absent
- redundant daemon coordinates removed
- hot path avoids host transcendental math
- SPARC dataset parsing stays Python-side
- C++ accepts a sanitized SPARC payload and returns emergent substrate velocities

## Quick Start

Compile and run the C++ simulator:

```powershell
.\compile_and_run.ps1
```

Generate charts from the simulator JSON:

```powershell
python .\fpm_axcore_plots.py
```

Run the full architecture and SPARC IPC test harness:

```powershell
python .\test_axcore_engine.py
```

The main simulator writes:

```text
artifacts/fpm_axcore_results.json
```

The SPARC host-to-substrate IPC test writes:

```text
artifacts/sparc_injection_payload.json
artifacts/sparc_substrate_output.json
```

## Architecture

![Architecture](artifacts/fpm_axcore_architecture.png)

The C++ engine stays intentionally narrow:

- Flat contiguous daemon arena, no per-node heap objects
- 6-face periodic `Z^3` adjacency
- `uint64_t` integer action steps
- 65-bucket radix heap scheduler
- deterministic fast-math in the hot path
- exact Layer 1 `N_bit_eq` precompute preserved

The Python layer acts as the host oracle and artifact surface:

- compiles/runs the C++ binary
- renders charts
- parses SPARC files
- creates sanitized injection payloads
- computes external RMSE from C++ returned velocities

That boundary matters. The C++ substrate should not crawl host data directories or parse large astronomy tables. It should accept a small payload, pay the thermodynamic routing cost, and return what the daemon ledger produces.

## Calibration Snapshot

From `artifacts/fpm_axcore_results.json`:

| Quantity | Value |
| --- | ---: |
| `N_bit_eq` | `1,452,997,909` |
| `alpha_PP` | `702.628349000451` |
| `G_FPM` | `6.68034009060519e-11` |
| `G` relative error | `0.0904977392%` |
| `n_s` | `0.968626331811263` |
| `n_s` relative error | `0.3757856799%` |
| `gamma_max` | `31.8738629472408` |
| `ell_D` | `1309.5687839896` |

![Calibration](artifacts/fpm_axcore_calibration.png)

## Emergent Probes

| Probe | Result |
| --- | --- |
| Born microcell quantization | `PASS` |
| Bell/CHSH torsion | `PASS` |
| Fine structure bare coupling | `PASS_BARE_COUPLING` |
| Time dilation gradient | measured |
| Emergent gravity route cost | measured |

Bell/CHSH:

| Quantity | Value |
| --- | ---: |
| `S_local` | `2.0` |
| `S_joint` | `2.82842722521771` |
| Tsirelson | `2.82842712474619` |

![Bell](artifacts/fpm_axcore_bell.png)

Born:

| Quantity | Value |
| --- | ---: |
| mean TV | `8.02009101805334e-10` |
| max TV | `1.32811210640238e-09` |

![Born](artifacts/fpm_axcore_born.png)

Fine structure:

| Quantity | Value |
| --- | ---: |
| `1/alpha_bare` | `136.805610371373` |
| relative difference | `0.00168122766402566` |

![Fine Structure](artifacts/fpm_axcore_fine_structure.png)

## Scheduler Trajectory

The toy lattice run uses `8 x 8 x 4 = 256` daemons. All remain active through the default run.

| Quantity | Value |
| --- | ---: |
| Active daemons | `256 / 256` |
| Tick count range | `[54, 55]` |
| Tick count std | `0.2802717362` |

![Trajectory](artifacts/fpm_axcore_trajectory.png)

## Emergent Gravity

The default C++ gravity probe injects a central baryonic load and measures the route-cost profile over shell radii.

| Radius | Emergent velocity km/s | Mean route cost `L` |
| ---: | ---: | ---: |
| `1` | `81442.1281493793` | `0.379378104486093` |
| `2` | `81462.6801040261` | `0.37928239241785` |
| `3` | `81479.8340820099` | `0.379202541963041` |
| `4` | `81499.5052976677` | `0.379111015334092` |
| `5` | `81495.9718941404` | `0.379127452369784` |
| `6` | `81493.0152153892` | `0.379141207635551` |
| `7` | `81477.8403802793` | `0.379211820765236` |

![Gravity](artifacts/fpm_axcore_gravity.png)

## Time Dilation

| Quantity | Value |
| --- | ---: |
| near gamma | `3.68094110610377` |
| far gamma | `3.67365140125124` |
| tick ratio | `1.0` |
| near ticks | `300` |
| far ticks | `300` |

![Time Dilation](artifacts/fpm_axcore_time_dilation.png)

## SPARC Host-to-Substrate IPC

The SPARC files live outside the engine. The Python oracle parses them and writes a tiny payload for one galaxy. The C++ substrate reads only that sanitized payload:

```json
{
  "galaxy": "DDO154",
  "points": [
    { "r_kpc": 0.49, "v_obs": 13.8, "b_load": 1.7099261376353714 }
  ]
}
```

Then the C++ binary runs:

```powershell
.\build\fpm_axcore.exe --sparc-payload artifacts\sparc_injection_payload.json --sparc-output artifacts\sparc_substrate_output.json
```

Latest DDO154 IPC result:

| Quantity | Value |
| --- | ---: |
| points | `12` |
| lattice | `32 x 32 x 4` |
| fitted scale | `134.967381386965` |
| RMSE | `10.6087636229365 km/s` |
| normalized RMSE | `0.277837545777474` |

The returned C++ raw substrate velocities are finite, monotone-ish, and derived from route-cost measurements:

```text
0.278819, 0.281055, 0.282023, 0.282681, 0.283223, 0.283800,
0.284367, 0.284864, 0.285064, 0.285136, 0.285146, 0.285004
```

This is the current bridge: Python handles astronomy file parsing; C++ pays the daemon-routing cost.

## Repository Layout

```text
.
├── src/
│   └── fpm_axcore_simulator.cpp
├── artifacts/
│   ├── fpm_axcore_results.json
│   ├── sparc_injection_payload.json
│   ├── sparc_substrate_output.json
│   └── *.png
├── compile_and_run.ps1
├── fpm_axcore_plots.py
└── test_axcore_engine.py
```

## Notes

- The engine is not a SPARC parser.
- The Python harness is not the physics engine.
- The IPC payload is the membrane between them.
- The current SPARC IPC test uses DDO154 as the first sanitized bridge case.
- Future dynamic torsion phase-lock tests should follow the same rule: keep orchestration outside, keep the substrate causal and deterministic.
