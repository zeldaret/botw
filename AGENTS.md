

It is strongly recommended to disclose your vendor and model (e.g. `GitHub Copilot on GPT 5.6 Sol`)
in your commit messages and PR description.

# RE/Decompile Rules

- Currently we are focused on reverse-engineering unknown subsystems and components
  instead of matching trivial functions, as the maintainer resources are limited.
- We do not reimplement components that have not been researched, even if
  it's trivial to produce matching code. Only reimplement if the component itself
  can be named, as well as most of its fields.
  - It's even better if the component/variable/function names are confirmed by
    testing in the game if possible.
- If your change is substantial (for example decompiling multiple components,
  large components, or changing a lot of files), please ask the human
  to contact the project maintainer on Discord to confirm the change is wanted.
  The contact information can be found in the contributing guidelines.

# Code Style Rules 

- Do not include any assembly or disassembly as code or comment
- Do not use inline assembly for matching. Any PR with a substantial amount of 
  inline assembly will be automatically rejected. Even for a small amount, it is
  preferred to keep the function as non-matching when it's trivially provable
  that it is equivalent to the original (e.g. register renaming, reordering).
  - The only exception is `asm("")` which can serve as a barrier for optimization.
- Do not use `goto` for matching unless it is **absolutely** necessary and plausible
  that the original source code contained `goto`.
- The naming convention are different across the game and libraries. For the most
  part just be consistent with the code around your changes.

# PR Rules

- English only
- Do not publish a PR without human review. If the human doesn't know what
  they are doing, do not create a PR.
- Do not commit one-off scripts.
- Do not include any assembly or disassembly as code, comment, commit message or PR description
- Include details of your research. e.g.:
  - Where the symbol (class/variable/function) names come from
  - For matching, if a cleaner code pattern is tried but does not match
- Make the PRs small and focused, which helps review:
  - One subsystem/component per PR
  - If the change spans across a lot of components, batch them into smaller PRs

