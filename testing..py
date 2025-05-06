users = {
    "admin" : "adminpass"
}

def login(username, password):
    if username in users and users[username] == password:
        print("Login Successful!")
        return True
    else:
        print("Invalid Username or Password")


def quiz():
    scientist = ["Mendeleyev, Dmitri", "Galilei, Galileo", "Newton, Isaac", "Dalton, John", "Einstein, Albert"]
    discoveries = ["Periodic Table", "Law of falling objects", "Laws of motion", "Atoms", "Relativity"]

    print(f"Welcome to the Famous Scientist and their Discoveries Quiz!")
    score = 0

    for i in range(len(scientist)):
        print(f"What is the discovery of {scientist[i]}?")
        answer = input("Your answer: ").strip()

        if answer.lower() == discoveries[i].lower():
            print("Correct!")
            score += 1
        else:
            print(f"Wrong answer. The correct answer is {discoveries[i]}")     

    print(f"Quiz finished your score is {score} out of {len(scientist)}")        

def main():
    print("Please Login \n")
    attempts = 3

    while attempts > 0:
        username = input("Please enter your username: ").strip()
        password = input("Please enter your password: ").strip()

    
        if login(username, password):
            print("Access Granted \n")
            quiz()
            break
        else:
            attempts -= 1
            print("Access Denied \n")            

    if attempts == 0:
        print("Too many failed attempts!! EXITING!!")

main()