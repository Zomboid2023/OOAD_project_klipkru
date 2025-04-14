import time
import subprocess
from flask import Flask, render_template, request, redirect, url_for, flash

app = Flask(__name__)
app.secret_key = 'your_secret_key'  # Required for flashing messages

@app.route('/')
def home():
    return render_template('index.html')

@app.route('/register_voter', methods=['GET', 'POST'])
@app.route('/register_voter', methods=['GET', 'POST'])
def register_voter():
    if request.method == 'POST':
        voter_id = request.form['voter_id']
        voter_name = request.form['voter_name']
        password = request.form['password']

        command = ['voting_app.exe', 'register_voter', voter_id, voter_name, password]

        try:
            process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
            stdout, stderr = process.communicate()

            if process.returncode != 0:
                return render_template('register_voter.html', message=f"Error: {stderr}", message_type='error')
            else:
                if "Voter ID already registered" in stdout:
                    return render_template('register_voter.html', message="Voter is already registered!", message_type='error')
                else:
                    return render_template('register_voter.html', message="Voter registered successfully!", message_type='success')

        except Exception as e:
            return render_template('register_voter.html', message=f"An error occurred: {e}", message_type='error')

    return render_template('register_voter.html')

@app.route('/cast_vote', methods=['GET', 'POST'])
def cast_vote():
    result = None
    candidates = []

    # Fetch candidates if the method is GET (when the page is loaded)
    if request.method == 'GET':
        try:
            # Call the C++ executable to get candidates
            process = subprocess.run(
                ['voting_app.exe', 'list_candidates'],
                capture_output=True,
                text=True
            )

            candidates = process.stdout.strip().split('\n')  # Assuming one candidate per line
            print(candidates)
        except Exception as e:
            candidates = [f"Error fetching candidates: {e}"]

    # Handle form submission when the user casts their vote
    if request.method == 'POST':
        voter_id = request.form['voter_id']
        password = request.form['password']
        candidate = request.form['candidate']
        candidate = int(candidate.split(",")[0].split(":")[1].strip())
        candidate = str(candidate)
        print(candidate)

        try:
            process = subprocess.run(
                ['voting_app.exe', 'cast_vote', voter_id, password, candidate],
                capture_output=True,
                text=True
            )
            result = process.stdout.strip() or process.stderr.strip()
            print(result)
        except Exception as e:
            result = f"An error occurred: {e}"

    return render_template('cast_vote.html', result=result, candidates=candidates)

if __name__ == '__main__':
    app.run(debug=True)
