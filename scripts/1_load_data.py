import re
import os
import shutil
import random
import zipfile
import urllib.request

from pathlib import Path

from .constants import VSBPPC_INSTANCES


class DataLoader:
    def __init__(self):
        self.urls = VSBPPC_INSTANCES

        self.base_dir  = Path('instances')
        self.train_dir = self.base_dir / 'train'
        self.test_dir  = self.base_dir / 'test'
        self.temp_dir  = Path('temp')

        self.item_counts = {1: 100, 2: 200, 3: 500, 4: 1000}
        self.size_intervals = {
            1: [1, 100],
            2: [20, 100], 
            3: [50, 100]
        }
        self.density_values = {
            0: 0.0, 1: 0.1, 2: 0.2, 3: 0.3, 4: 0.4, 5: 0.5,
            6: 0.6, 7: 0.7, 8: 0.8, 9: 0.9, 10: 0.95, 11: 0.99
        }
    
    def create_directories(self):
        """Cria as pastas necessárias para organizar os dados."""
        print("Criando diretórios...")
        self.train_dir.mkdir(parents=True, exist_ok=True)
        self.test_dir.mkdir(parents=True, exist_ok=True)
        self.temp_dir.mkdir(exist_ok=True)
        print(f"✓ Diretórios criados: {self.train_dir}, {self.test_dir}")
    
    def download_file(self, url: str, filename: str) -> bool:
        """Baixa um arquivo da URL especificada."""
        try:
            print(f"Baixando {filename}...")
            urllib.request.urlretrieve(url, self.temp_dir / filename)
            print(f"✓ {filename} baixado com sucesso")
            return True
        except Exception as e:
            print(f"✗ Erro ao baixar {filename}: {e}")
            return False
    
    def extract_zip(self, zip_filename: str) -> List[str]:
        """Extrai arquivos .txt de um arquivo .zip."""
        extracted_files = []
        zip_path = self.temp_dir / zip_filename
        
        try:
            with zipfile.ZipFile(zip_path, 'r') as zip_ref:
                # Lista todos os arquivos .txt no zip
                txt_files = [f for f in zip_ref.namelist() if f.endswith('.txt')]
                
                for txt_file in txt_files:
                    # Extrai o arquivo
                    zip_ref.extract(txt_file, self.temp_dir)
                    extracted_files.append(txt_file)
                    
            print(f"✓ {len(extracted_files)} arquivos .txt extraídos de {zip_filename}")
            return extracted_files
            
        except Exception as e:
            print(f"✗ Erro ao extrair {zip_filename}: {e}")
            return []
    
    def parse_filename(self, filename: str) -> Tuple[int, int, int, int]:
        """Extrai os parâmetros do nome do arquivo no formato Correia_Random_x_y_z_t.txt."""
        # Remove o caminho e pega apenas o nome do arquivo
        basename = os.path.basename(filename)
        
        # Padrão regex para extrair os parâmetros
        pattern = r'Correia_Random_(\d+)_(\d+)_(\d+)_(\d+)\.txt'
        match = re.match(pattern, basename)
        
        if match:
            x, y, z, t = map(int, match.groups())
            return x, y, z, t
        else:
            raise ValueError(f"Formato de arquivo inválido: {filename}")
    
    def organize_files(self, all_files: List[str]):
        """Organiza os arquivos em treino e teste de forma balanceada."""
        print("Organizando arquivos em treino e teste...")
        
        # Agrupa arquivos por configuração (x, y, z)
        config_groups: Dict[Tuple[int, int, int], List[str]] = {}
        
        for file_path in all_files:
            try:
                x, y, z, t = self.parse_filename(file_path)
                config = (x, y, z)
                
                if config not in config_groups:
                    config_groups[config] = []
                config_groups[config].append(file_path)
                
            except ValueError as e:
                print(f"Aviso: {e}")
                continue
        
        # Para cada configuração, seleciona 8 para treino e 2 para teste
        for config, files in config_groups.items():
            x, y, z = config
            print(f"Configuração (x={x}, y={y}, z={z}): {len(files)} arquivos")
            
            # Ordena os arquivos para garantir consistência
            files.sort()
            
            # Seleciona 8 para treino e 2 para teste
            train_files = files[:8]
            test_files = files[8:10] if len(files) >= 10 else []
            
            # Move arquivos para as pastas apropriadas
            for file_path in train_files:
                source_path = self.temp_dir / file_path
                dest_path = self.train_dir / os.path.basename(file_path)
                if source_path.exists():
                    shutil.move(str(source_path), str(dest_path))
            
            for file_path in test_files:
                source_path = self.temp_dir / file_path
                dest_path = self.test_dir / os.path.basename(file_path)
                if source_path.exists():
                    shutil.move(str(source_path), str(dest_path))
        
        print(f"✓ Arquivos organizados: {len(list(self.train_dir.glob('*.txt')))} em treino, "
              f"{len(list(self.test_dir.glob('*.txt')))} em teste")
    
    def cleanup(self):
        """Remove arquivos temporários."""
        print("Limpando arquivos temporários...")
        if self.temp_dir.exists():
            shutil.rmtree(self.temp_dir)
        print("✓ Limpeza concluída")
    
    def run(self):
        """Executa o processo completo de carregamento de dados."""
        print("=== Carregamento de Dados VSBPPC ===")
        
        # Cria diretórios
        self.create_directories()
        
        # Lista para armazenar todos os arquivos extraídos
        all_extracted_files = []
        
        # Baixa e extrai cada arquivo
        for url in self.urls:VSBPPC_INSTANCES
            filename = url.split('/')[-
            
            # Baixa o arquivo
            if self.download_file(url, filename):
                # Extrai os arquivos .txt
                extracted_files = self.extract_zip(filename)
                all_extracted_files.extend(extracted_files)
        
        # Organiza os arquivos em treino e teste
        if all_extracted_files:
            self.organize_files(all_extracted_files)
        
        # Limpa arquivos temporários
        self.cleanup()
        
        print("\n=== Resumo ===")
        train_count = len(list(self.train_dir.glob('*.txt')))
        test_count = len(list(self.test_dir.glob('*.txt')))
        print(f"Arquivos de treino: {train_count}")
        print(f"Arquivos de teste: {test_count}")
        print(f"Total: {train_count + test_count}")
        print("\n✓ Carregamento de dados concluído!")


def main():
    """Função principal."""
    loader = DataLoader()
    loader.run()


if __name__ == "__main__":
    main()
