# Changelog

## v2.17 (persistent destination count)

The version screen shows `2.17`. Expected patched-file SHA-256:
`505108d89b2be42d1fac772c8b04bef22052f8dd087bf09a539c503f8649f714`.

- Continuously restores the selected `C02`–`C16` after Roland's normal play-page refresh, so the count remains visible until the destination pad is pressed.
- Adds a regression test in which the stock refresh deliberately redraws the source sample number before the chop UI restores `Cxx`.
- Keeps gated destinations and all v2.16 processing feedback unchanged.

## v2.16 (stable count display and gated chops)

The version screen shows `2.16`. Expected patched-file SHA-256:
`412fcb2e9aa2beb546deca2fa87532b708caa70f17308276e225a0e397c1eefd`.

- Removes the immediate `Pad` prompt; the selected `Cxx` remains visible until a destination pad is pressed.
- Every generated chop now has GATE enabled, regardless of the source pad's setting.
- Keeps the flexible 2–16 count, persistent `ChP`, MARK blink, `don`, and `Err` feedback.

## v2.15 (destination prompt and flexible slice count)

The version screen shows `2.15`. Expected patched-file SHA-256:
`2062c7d953f75ee1621a8b83d2a6d4375820e2db7f6416ec0aa17804118e5e54`.

- CTRL 3 now selects every slice count from 2 through 16, with 4 still the default.
- Shows `Pad` until the first destination pad is pressed.
- Keeps `ChP` visible for the complete copy/mark batch, then shows `don`.
- Leaves per-pad progress numbers and destination-pad flashing for a future alternative.

## v2.14 (auto-slice processing feedback)

The version screen shows `2.14`. Expected patched-file SHA-256:
`074b37745cc4e1b114e3eefd83990dcd557b1a25cd84132b94eb015d49014f42`.

- Shows `ChP` and blinks the MARK light after a valid destination is selected.
- Shows `don` and stops the blink only after the copy batch and final mark save complete.
- Shows `Err` and stops the blink if the native copy worker fails.
- Keeps the hardware-confirmed v2.13 CANCEL + MARK gesture and slice engine unchanged.

## v2.13 (corrected panel mapping)

The version screen shows `2.13`. Expected patched-file SHA-256:
`e3d21b2c2d6746e618f2403cce25210df17fb9e3b250394dce9b3159859e06ec`.

- Auto-slice now opens with **CANCEL + MARK**.
- Corrects MARK's panel ID to 36. The earlier ID 44 is SUB PAD, explaining why v2.11 and v2.12 never saw a
  physical MARK press.
- Removes the unnecessary Remain-page hook added in v2.12. The slice planner, copy worker and existing v2.10
  features are unchanged.
- Reserves FUNC + MARK as a candidate for a future lazy-chop workflow.

## v2.12 (sample-chop hardware fix)

The version screen shows `2.12`. Expected patched-file SHA-256:
`c6d10f587f607c8d855d94f5cee0b72136d9a8dc21ed215168b9d06a1760c2ef`.

- Attempted to fix REMAIN + MARK by also hooking Roland's dedicated Remain page. Hardware later showed this
  was insufficient because MARK had been mapped to SUB PAD's ID; v2.13 supersedes this release.
- No changes to the slice planner, copy worker, LIGHTS region or existing v2.10 features.

## v2.11 (sample-chop test release)

The version screen shows `2.11`. Expected patched-file SHA-256:
`658445118e825f13da4e8014a921e29d1003cdaef2b1a132ff67d067a084fd80`.

- Adds auto-slice/chop: play a source pad, hold REMAIN and press MARK, choose 4/8/12/16 slices with CTRL 3,
  choose the destination bank and first pad, then press MARK to create the consecutive chopped pads.
- Checks the complete destination range before copying; `FUL` means the requested run will not fit or is not
  available. CANCEL exits without changing pads.
- Retains the v2.10 chromatic, resampling, copy/exchange and varispeed features.
- This is a hardware-test release. The patcher source and reverse-engineering notes are public; no firmware
  binary is stored in the repository.

## v2.10

The version screen shows `2.10`. Output `sp404sx_up.bin` SHA-256
`733885e5935d0c2c4c887f0446afa8e2546d2520223cec7ccbe9297c08066b54`.

- **Chromatic mode per bank:** SHIFT + TIME/BPM opens a chromatic menu for the last pad played (TIME/BPM
  blinks) and makes its bank a keyboard for it: pad 1 = own pitch, + 1 semitone per pad. CTRL 1 MIDI channel
  (free ones only) or OFF, CTRL 2 mono (poly later), CTRL 3 octave −2 … +2. Several banks at once.
  MIDI on a bank's channel: note 60 = own pitch, silent above B6. Saved in `CHROMA.BIN`. SHIFT + TIME/BPM or
  TIME/BPM leaves the menu. Pads of a chromatic bank don't close the TIME/BPM or START/END/LEVEL page, and HOLD
  works on every pad of the bank.
- While resampling (`RDY` / `REC`) every MIDI note plays like a pad press, and the first one starts the
  recording (stock ignores MIDI notes while sampling).
- Varispeed now follows the sample on copy and exchange even between identical samples (it is moved when
  Roland's copy / exchange finishes, instead of only by matching sample fingerprints).
- The resampler handles speeds up to just under 8× (chromatic notes); PTN keeps its 4× limit.

## v2.00

First public release, a full new version over Roland's system 1.07, for the SP-404SX and SP-404A.
The version screen shows `2.00`. Output `sp404sx_up.bin`
SHA-256 `3093b7e677e285e4dd1f612d9f9ccc0df6e364998bc79f1ec52df0b9c11a7ffd`.

- **Varispeed on CTRL 3** (TIME/BPM page): per-pad tape-style speed. Fully left OFF, −12 to +7 semitones,
  fully right PTN.
- **PTN** follows the pattern tempo live, 0.25× to 4×, the same tempo Roland's Time Modify PTN uses.
- The display shows the BPM you hear on CTRL 3, CTRL 1 and CTRL 2; the CTRL 3 view stays on screen and the
  TIME/BPM button stays lit.
- Works with Time Modify; CTRL 2 resets varispeed as it resets Time Modify.
- Speeds saved on the card (`VARISPD.BIN`) and following the sample on copy and exchange.
- Version screen (hold MARK at power-on) shows `2.00`.
- Roland's factory hardware-test mode removed to make room.
- [Web patcher](https://good-scoop-labs.github.io/sp-404sx-extrafirmware/) (GitHub Pages, `docs/index.html`) and Python patcher (`patch.py`) with identical results.

Development history (internal test builds 1 to 13) is in [docs/DEV_NOTES.md](docs/DEV_NOTES.md).
