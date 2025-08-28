import re
import ssl
import random
import shutil
import zipfile
import urllib.request

from pathlib     import Path
from collections import defaultdict

from .constants import ITEM_COUNTS     , \
                       SIZE_INTERVALS  , \
                       DENSITY_VALUES  , \
                       INSTANCE_PATTERN, \
                       VSBPPC_INSTANCES


class DataLoader:
    def __init__(self):
        self.urls = VSBPPC_INSTANCES

        self.base_dir  = Path('instances')
        self.train_dir = self.base_dir / 'train'
        self.test_dir  = self.base_dir / 'test'
        self.temp_dir  = Path('temp')

        self.instance_pattern = INSTANCE_PATTERN

        self.item_counts    = ITEM_COUNTS
        self.size_intervals = SIZE_INTERVALS
        self.density_values = DENSITY_VALUES

    def create_directories(self):
        print("Creating directories...")

        self.train_dir.mkdir(parents=True, exist_ok=True)
        self.test_dir .mkdir(parents=True, exist_ok=True)
        self.temp_dir .mkdir(exist_ok=True)

    def download_file(self, url, filename):
        try:
            print(f"Downloading {filename}...")

            context = ssl._create_unverified_context()

            with urllib.request.urlopen(url, context=context) as response:
                with open(self.temp_dir / filename, "wb") as out_file:
                    shutil.copyfileobj(response, out_file)

            return True
        except Exception as e:
            print(f"✗ Error downloading {filename}: {e}")

            return False

    def extract_zip(self, zip_filename):
        zip_path = self.temp_dir / zip_filename

        extracted_files = []
        try:
            with zipfile.ZipFile(zip_path, 'r') as zip_ref:
                txt_files = [
                    f
                    for f in zip_ref.namelist()
                    if f.endswith('.txt')
                ]

                for txt_file in txt_files:
                    zip_ref.extract(txt_file, self.temp_dir)

                    extracted_files.append(txt_file)

            print(f"✓ {len(extracted_files)} .txt files extracted from {zip_filename}")
        except Exception as e:
            print(f"✗ Error extracting {zip_filename}: {e}")

        return extracted_files

    def parse_filename(self, filename):
        match = re.match(
            self.instance_pattern,
            Path(filename).name  ,
        )

        if match:
            return map(int, match.groups())
        else:
            raise ValueError(f"Invalid file format: {filename}")

    def organize_files(self, all_files):
        print("Organizing files into training and testing sets...")

        config_groups = defaultdict(list)

        for file_path in all_files:
            try:
                x, y, z, _ = self.parse_filename(file_path)

                config_groups[(x, y, z)].append(file_path)
            except ValueError as e:
                print(f"Warning: {e}")
                continue

        for (x, y, z), files in config_groups.items():
            print(f"Config (x={x}, y={y}, z={z}): {len(files)} files")

            random.shuffle(files)

            self.move_files(self.temp_dir, files[ :8], self.train_dir)
            self.move_files(self.temp_dir, files[8: ], self.test_dir )

        print(f"✓ Files in train:")
        print(
            '\n'.join(
                f.name
                for f in self.train_dir.glob('*.txt')
            )
        )

        print()

        print("Files in test:")
        print(
            '\n'.join(
                f.name
                for f in self.test_dir.glob('*.txt')
            )
        )

    def cleanup(self):
        print("Removing temporary files...")

        if self.temp_dir.exists():
            shutil.rmtree(self.temp_dir)

    def run(self):
        print("=== VSBPPC Data Loading ===")

        self.create_directories()

        all_extracted_files = []
        for url in self.urls:
            filename = url.split('/')[-1]

            if self.download_file(url, filename):
                all_extracted_files.extend(
                    self.extract_zip(filename)
                )

        if all_extracted_files:
            self.organize_files(all_extracted_files)

        self.cleanup()

        print()

        print("=== Summary ===")
        print(f"Training files: {len(list(self.train_dir.glob('*.txt')))}")
        print(f"Testing files : {len(list(self.test_dir.glob('*.txt')))}" )
        print("✓ Data loading complete!")

    @staticmethod
    def move_files(dirname, files, dest_dir):
        for file_path in files:
            source_path = dirname / file_path
            dest_path   = dest_dir / Path(file_path).name

            if source_path.exists():
                shutil.move(
                    str(source_path),
                    str(dest_path  )
                )


if __name__ == "__main__":
    loader = DataLoader()
    loader.run()
