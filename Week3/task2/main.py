import hashlib
import os
import pyautogui

def generate_salt():
    salt = os.urandom(16)
    print(f'Generated salt: {salt.hex()}')
    return salt

def hash_password(password, salt):
    hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode('utf-8'), salt, 100000)
    print(f'Hashed password: {hashed_password.hex()}')
    return hashed_password

def save_user(username, hashed_password, salt, filename='passwords.txt'):
    with open(filename, 'a') as file:
        print(f'Saving user: {username}:{hashed_password.hex()}:{salt.hex()}')
        file.write(f'{username}:{hashed_password.hex()}:{salt.hex()}\n')

def authenticate_user(username, password, filename='passwords.txt'):
    with open(filename, 'r') as file:
        for line in file:
            stored_username, stored_password, stored_salt = line.strip().split(':')
            if stored_username == username:
                hashed_password = hash_password(password, bytes.fromhex(stored_salt))
                if hashed_password.hex() == stored_password:
                    return True
    return False

def main():
    # Use PyAutoGUI to input username
    username = pyautogui.prompt("Enter your username: ").strip()

    # Use PyAutoGUI to input password securely
    password = pyautogui.password("Enter your password: ").strip()

    salt = generate_salt()
    hashed_password = hash_password(password, salt)

    save_user(username, hashed_password, salt)

    # Authenticate user
    if authenticate_user(username, password):
        print("Authentication successful!")
    else:
        print("Authentication failed.")

if __name__ == "__main__":
    main()
