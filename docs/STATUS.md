# Status

What has been confirmed on hardware, and what hasn't yet. Release v2.10 = test build v2.10c (byte-identical).
Release v2.00 = internal build 13 plus the `2.00` version screen. The SP-404SX and SP-404A run the same firmware, so this applies to both.

## v2.19 stock-equivalent START/END writes

Checked in software:
- The chop worker now follows the stock UI call pattern: GET 31, SET 32 for START, and GET/SET 33 for absolute END.
- Every generated END equals the following slice's START, including uneven divisions and an edited source START.
- All host tests pass: 1,371 chop checks, 1,080 resampler cases, and the 308-million-output stress test.
- The web patcher output is byte-identical to the native build.
- Native output SHA-256: `05d077fc8305d0451757b480d4ea5c98f294d37bc7a67e2b0ca2b6375d626e12`.

Awaiting hardware confirmation:
- Confirm `2.19`, distinct sequential regions, and that every END marker sits at the next chop's START.

## v2.18 definite chop regions

Checked in software:
- Parameter 33 is supplied with each slice's length; Roland stores END as START + length.
- Every generated END equals the following slice's START, including uneven divisions and sources with edited marks.
- The host persistence mock now models the native relative-END behavior.
- Native output SHA-256: `3d8ac1292ff6b47a1d05c48bf98c7ae69cf4ed6241cf430f850294a02963c618`.

Hardware result:
- Failed: END markers remained incorrect and the final chop became extremely short. This exposed the incorrect relative-END model; v2.19 replaces it with the stock editor's parameter path.

## v2.17 persistent destination count

Checked in software:
- While destination selection is active, every play-page refresh restores the selected `Cxx` after Roland redraws the current sample number.
- The host UI test now simulates that stock overwrite and verifies that `Cxx` wins.
- GATE = 1, persistent `ChP`, final `don`, failure `Err`, and the 2–16 count range are unchanged.
- Native output SHA-256: `505108d89b2be42d1fac772c8b04bef22052f8dd087bf09a539c503f8649f714`.

Awaiting hardware confirmation:
- Confirm `2.17` and that `Cxx` remains visible indefinitely until the destination pad is pressed.

## v2.16 stable count display and gated chops

Checked in software:
- The selected `Cxx` remains visible until the first destination pad is pressed; the immediate `Pad` prompt is removed.
- Every generated destination is explicitly written with GATE = 1.
- Persistent `ChP`, final `don`, failure `Err`, and the 2–16 count range remain unchanged.
- Native output SHA-256: `412fcb2e9aa2beb546deca2fa87532b708caa70f17308276e225a0e397c1eefd`.

Awaiting hardware confirmation:
- Confirm `2.16`, stable `Cxx`, gated destination pads, persistent `ChP`, and final `don`.

## v2.15 destination prompt and flexible slice count

Checked in software:
- `C04` remains the default; CTRL 3 selects every count from `C02` through `C16`.
- `Pad` prompts for the first destination pad.
- `ChP` is redrawn throughout processing, then changes to `don`; `Err` remains the failure message.
- Per-destination numbers and pad flashing are deliberately deferred.
- Native output SHA-256: `2062c7d953f75ee1621a8b83d2a6d4375820e2db7f6416ec0aa17804118e5e54`.

Awaiting hardware confirmation:
- Confirm `2.15`, the full 2–16 CTRL 3 range, `Pad`, persistent `ChP`, and final `don`.

## v2.14 processing feedback

Checked in software:
- Builds on the hardware-confirmed v2.13 CANCEL + MARK gesture.
- Shows `ChP` and blinks MARK during the copy/mark batch.
- Shows `don` and stops the MARK blink after all slice marks are saved; `Err` reports a worker failure.
- Native output SHA-256: `074b37745cc4e1b114e3eefd83990dcd557b1a25cd84132b94eb015d49014f42`.

Awaiting hardware confirmation:
- Hold MARK during power-on and confirm `2.14`, then run an auto-slice and confirm `ChP`/blink changes to `don`/off.

## v2.13 corrected panel mapping

Checked in software:
- Auto-slice uses CANCEL (ID 34) + MARK (ID 36). ID 44 is SUB PAD, not MARK.
- The v2.12 Remain-page hook is removed; only the existing Play-page hook is needed.
- Native build, Python patcher and browser patcher are byte-identical. Output SHA-256:
  `e3d21b2c2d6746e618f2403cce25210df17fb9e3b250394dce9b3159859e06ec`.
- All host UI, resampler, persistence, chromatic, chop and stress tests pass.

Hardware confirmed: CANCEL + MARK opens the slicer and the slice batch works.

## v2.12 sample-chop hardware fix

Superseded: hardware confirmed `2.12` installed, but the gesture still did not open. The underlying MARK/SUB
PAD mapping error was corrected in v2.13.

Checked in software:
- Hooks both the Play page and Roland's dedicated Remain page, so the MARK press following REMAIN reaches the
  chop UI. The original Remain-page handler still runs for events the chop UI does not consume.
- Native build, Python patcher and browser patcher are byte-identical. Output SHA-256:
  `c6d10f587f607c8d855d94f5cee0b72136d9a8dc21ed215168b9d06a1760c2ef`.
- All host UI, resampler, persistence, chromatic, chop and stress tests pass.

The intended hardware checks were:
- Hold MARK during power-on and confirm `2.12`, then play a loaded sample and press REMAIN followed by MARK;
  `C04` should appear.

## v2.11 sample-chop test release

Superseded by v2.13 because the gesture used SUB PAD's ID instead of MARK's ID.

Checked in software:
- Displayed fork version is `2.11`; Roland's underlying updater version remains 1.07.
- Auto-slice UI and native batch-copy/mark planner are covered by host tests.
- The Python patcher, browser patcher and native builder produce byte-identical output with SHA-256
  `658445118e825f13da4e8014a921e29d1003cdaef2b1a132ff67d067a084fd80`.
- The reused factory-test region fits with 76 bytes free; the LIGHTS region remains sealed and unchanged.

Awaiting hardware confirmation:
- Hold MARK during power-on and confirm the display says `2.11`.
- Play a sample, then hold REMAIN and press MARK; confirm `C04` appears.
- Confirm CTRL 3 selects 2–16, destination selection works across banks, CANCEL exits safely, and `FUL`
  appears when the complete destination run is unavailable.
- Confirm the created pads contain consecutive slices and existing v2.10 features still work.

## v2.10

Confirmed on hardware (test builds E1 … v2.10c):
- Chromatic mode: SHIFT + TIME/BPM opens the menu (TIME/BPM blinks) and makes the last pad's bank a keyboard;
  all 12 pads play in semitones, including empty ones; loop pads switch notes correctly.
- Menu: CTRL 1 MIDI channel (free ones only, OFF fully left), CTRL 2 `MON`, CTRL 3 octave; leaving with
  TIME/BPM or SHIFT + TIME/BPM, and with another pad when the bank is OFF.
- MIDI on a bank's channel (note 60 = own pitch); `C.ON` on the main screen.
- Resampling: chromatic pads and MIDI play at `RDY` / `REC`, and any MIDI note starts the recording.
- TIME/BPM and START/END/LEVEL pages stay open for pads of a chromatic bank; HOLD on every key; MARK keeps
  the chromatic pitch.
- Varispeed follows copy and exchange, including between identical samples.
- Version screen `2.10`.

Not tested yet:
- Several chromatic banks at once on different channels, and `CHROMA.BIN` across power cycles with them.
- A chromatic source whose sample is deleted or replaced (the bank should turn off).
- Pattern playback and pattern recording with chromatic banks (should play the source at its own pitch).

## v2.00

### Confirmed on hardware

- Installing through Roland's normal card update, and going back to stock with Roland's original file.
- CTRL 3 varispeed: audible speed change, display BPM, OFF position, normal playback elsewhere.
- PTN locking to the pattern tempo and following tempo changes.
- CTRL 1 / CTRL 2 showing the tempo you hear; CTRL 2 resetting varispeed.
- Saving across power cycles; copy, exchange, delete, recording and resampling with varispeed pads.
- TIME/BPM light staying on, and the CTRL 3 view staying on screen.
- Everyday use of the rest of the sampler (effects, recording, patterns) unchanged.

### Not tested yet

- The `2.00` version screen text (two digit offsets in Roland's version routine; the same kind of change
  as internal test build 1, which was confirmed on hardware).
- **Many fast PTN pads at once** (up to 4× sample reading): possible dropouts.
- The TIME/BPM page's automatic exit in pattern mode while the CTRL 3 view is shown (one-byte fix found
  in a code review; matches Roland's behaviour for the CTRL 1 / CTRL 2 views).

### Checked in software

- Every changed byte maps to a planned patch; Roland code that would branch into, point into or load
  constants from reused areas was ruled out by the build checks.
- Host tests (`src/tests`): resampler bit-exact against a reference in 760 cases; 300 million samples under
  AddressSanitizer / UBSan; 16 persistence cases; 52 TIME/BPM page cases.
- Both patchers give a byte-identical file to the build (`src/tools/check_web_patch.js`).

## Known limits

See "Limits and notes" in the [user guide](USER_GUIDE.md#limits-and-notes).
