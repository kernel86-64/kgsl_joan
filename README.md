# KGSL on the LG V30 (joan)

This fork ports Qualcomm's open KGSL driver to the LG V30 (MSM8998, Adreno
540) on mainline Linux, for the LineageOS 24.0 (Android 17) port.

| Branch | Kernel | Status |
|---|---|---|
| `joan-7.3` | Linux 7.3 | current: OpenGL ES 3.2 (`V@0490.0`) and Vulkan 1.1.128, six consecutive sleep/wake/unlock cycles, RGB565 scanout colours fixed |
| `joan-6.18` | Linux 6.18 | earlier bring-up, kept for reference |

Pair it with [ion_legacy](https://github.com/kernel86-64/ion_legacy), which
provides the 64-bit `/dev/ion` ABI over the mainline dma-buf heaps. Both are
used with `msm.separate_gpu_kms=1`: DRM owns the display, KGSL owns the GPU.

Changes on top of the upstream driver:

- `adreno`: skip the 27 MHz slumber OPP that the mainline msm8998 DT carries;
  it has no DDR bandwidth and must never become the default KGSL power level.
- `kgsl_iommu`: never touch the per-context SMMU registers once the global
  registers are secured, otherwise the XPU hard-resets the SoC after the zap
  shader on joan.
- `adreno_a5xx`: clear `ADRENO_DEVICE_GPMU_INITIALIZED` before the RBBM
  software reset in `a5xx_start()`, so the GPMU is re-initialised.

Build against an Android kernel tree:

```sh
make -C <kernel> M=$PWD O=<kernel-out> ARCH=arm64 LLVM=1 modules
```

The LineageOS device tree does not build this module by default yet; the test
device currently loads it separately. See
[android_device_lge_joan](https://github.com/kernel86-64/android_device_lge_joan)
for the port itself.

---

# KGSL (Kernel Graphics Support Layer) Driver

This repository contains the source code of KGSL driver for the Adreno family
of GPUs. Required to use hardware accelerated OpenGL, compute and Vulkan on
Qualcomm Snapdragon targets.

KGSL is responsible for:
- GPU memory management
- Command submission to GPU
- GPU Power management
- Providing debug and profiling interface to userspace

# Branches

Primary development branch: gfx-kernel.le.0.0

# How-to-Build

This source code can be built using recipe file related to kgsl in meta-qcom
project, which is designed for Qualcomm-based platforms.

Steps for compilation:
- Modify the KGSL driver code as required and generate a corresponding patch
  file.
- Git clone meta-qcom project https://github.com/qualcomm-linux/meta-qcom.git .
- Integrate the patch into the kgsl related recipe file located at
  meta-qcom/recipes-graphics.
- Compile the project. Please refer to the README.md file provided in the
  meta-qcom repository.

# Getting in Contact

Problems specific to the KGSL driver can be reported in the Issues section of
this repository.

# License
This driver is released under the GPL-2.0 license. See LICENSE.txt for details.
