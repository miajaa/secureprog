from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import hashes
import os
import hashlib
import pyautogui


def generate_key(password, salt):
    # Key derivation function using PBKDF2 (Password-Based Key Derivation Function 2) with SHA256
    kdf = PBKDF2HMAC(
        algorithm=hashes.SHA256(),
        iterations=100000,
        salt=salt,
        length=32,
        backend=default_backend()
    )
    # Derive the key from the password and salt
    key = kdf.derive(password)
    return key


def encrypt_file(file_path, key):
    # Read the plaintext from the file
    with open(file_path, 'rb') as file:
        plaintext = file.read()

    # Generate a random Initialization Vector (IV)
    iv = os.urandom(16)

    # Create an AES cipher with CFB mode
    cipher = Cipher(algorithms.AES(key), modes.CFB(iv))

    # Encrypt the plaintext
    encryptor = cipher.encryptor()
    ciphertext = encryptor.update(plaintext) + encryptor.finalize()

    # Write the IV and ciphertext to the encrypted file
    with open(file_path + '.enc', 'wb') as encrypted_file:
        encrypted_file.write(iv + ciphertext)


def decrypt_file(file_path, key):
    # Read the IV and ciphertext from the encrypted file
    with open(file_path, 'rb') as encrypted_file:
        data = encrypted_file.read()

    # Extract the IV and ciphertext
    iv = data[:16]
    ciphertext = data[16:]

    # Create an AES cipher with CFB mode
    cipher = Cipher(algorithms.AES(key), modes.CFB(iv))

    # Decrypt the ciphertext
    decryptor = cipher.decryptor()
    plaintext = decryptor.update(ciphertext) + decryptor.finalize()

    # Write the decrypted plaintext to a new file
    with open(file_path[:-4] + '_decrypted.txt', 'wb') as decrypted_file:
        decrypted_file.write(plaintext)


def main():
    # Use PyAutoGUI to input username
    username = pyautogui.prompt("Enter your username: ").strip()

    # Use PyAutoGUI to input password securely
    password = pyautogui.password("Enter your password: ").strip()

    # Load user credentials from the file
    file_path = r'C:\Users\Johanna\Documents\secureprog\Week3\task2\passwords.txt'
    with open(file_path, 'r') as credentials_file:
        lines = credentials_file.readlines()

    for line in lines:
        # Extract username, stored password, and stored salt from each line
        stored_username, stored_password, stored_salt = line.strip().split(':')

        # Check if the entered username matches a stored username
        if username == stored_username:
            # Hash the entered password using stored salt
            hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), bytes.fromhex(stored_salt),
                                                  100000)

            # Check if the hashed password matches the stored password
            if hashed_password.hex() == stored_password:
                print("Authentication successful!")
                salt = bytes.fromhex(stored_salt)
                key = generate_key(hashed_password, salt)

                # Use PyAutoGUI to input file path for encryption
                file_to_encrypt = pyautogui.prompt("Enter the path of the file to encrypt: ").strip()

                # Encrypt the file
                encrypt_file(file_to_encrypt, key)
                print("File encrypted successfully.")

                # Decrypt the file
                decrypt_file(file_to_encrypt + '.enc', key)
                print("File decrypted successfully.")

                break
    else:
        print("Authentication failed.")


if __name__ == "__main__":
    main()
