## INSTANCES

The problem instances used to evaluate the proposed algorithms can be found at the following [link](https://faculty.ozyegin.edu.tr/aliekici/researchdata/).

### About the Instances

The files in this folder are benchmark instances for the Variable-Sized Bin Packing Problem with Conflicts (VSBPPC). Each file name follows the pattern:

```
Correia_Random_<item_count>_<size_interval>_<density>_<seed>.txt
```

Where:
- `<item_count>`   : Number of items in the instance
- `<size_interval>`: Interval used for item sizes
- `<density>`      : Conflict graph density
- `<seed>`         : Instance number

### How to Obtain the Instances

The instances are automatically downloaded and organized by the script `scripts/1_load_instances.py`. To download and organize the instances, run:

```bash
python3 -m scripts.1_load_instances
```

This script will:
- Download the original instance archives from the official repository
- Extract the `.txt` files
- Randomly split them into `train/` and `test/` folders for reproducible experiments
