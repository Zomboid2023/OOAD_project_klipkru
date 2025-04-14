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

@app.route('/admin_login', methods=['GET', 'POST'])
def admin_login():
    if request.method == 'POST':
        password = request.form['password']
        
        try:
            process = subprocess.run(
                ['voting_app.exe', 'login_admin', password],
                capture_output=True,
                text=True
            )
            output = process.stdout.strip()
            
            if "successful" in output.lower():
                flash("Admin login successful!", "success")
                return redirect(url_for('admin_dashboard'))
            else:
                return render_template('admin_login.html', message="Invalid admin password!", message_type='error')
        except Exception as e:
            return render_template('admin_login.html', message=f"An error occurred: {e}", message_type='error')

    return render_template('admin_login.html')

@app.route('/admin_dashboard')
def admin_dashboard():
    return render_template('admin_dashboard.html')

@app.route('/add_candidate', methods=['GET', 'POST'])
def add_candidate():
    message = None
    message_type = None

    if request.method == 'POST':
        candidate_name = request.form['candidate_name']
        try:
            process = subprocess.run(
                ['voting_app.exe', 'register_candidate', candidate_name],
                capture_output=True,
                text=True
            )
            if "already exists" in process.stdout:
                message = "Candidate already exists!"
                message_type = "error"
            elif process.returncode == 0:
                message = "Candidate registered successfully!"
                message_type = "success"
            else:
                message = f"Error: {process.stderr}"
                message_type = "error"
        except Exception as e:
            message = f"An error occurred: {e}"
            message_type = "error"

    return render_template('add_candidate.html', message=message, message_type=message_type)

@app.route('/view_voters')
def view_voters():
    voters = []
    try:
        process = subprocess.run(
            ['voting_app.exe', 'view_voters'],
            capture_output=True,
            text=True
        )
        if process.returncode == 0:
            voters = process.stdout.splitlines()  # Assuming each voter is on a new line
        else:
            voters = ["Error fetching voters. Try again later."]

        voters = voters[2:]
        # print(voters)

        f = []
        for i in voters:
            f.append(",".join(item.split(":")[1].strip() for item in i.split(",")))
        # print(f)     
        voters = f
    except Exception as e:
        voters = [f"An error occurred: {e}"]

    return render_template('view_voters.html', voters=voters)

@app.route('/election_results')
def election_results():
    results = []
    try:
        process = subprocess.run(
            ['voting_app.exe', 'view_results'],
            capture_output=True,
            text=True
        )
        if process.returncode == 0:
            results = process.stdout.splitlines()
        else:
            results = ["Error fetching election results."]
        # print(results)
        results = results[2:]
        f = []
        for i in results:
            i = i.split()[0:2]
            i[0] = i[0][:-1]
            f.append(i)

        # print(f)
        results = f
    except Exception as e:
        results = [f"An error occurred: {e}"]

    return render_template('election_results.html', results=results)

@app.route('/view_ledger')
def view_ledger():
    try:
        output = subprocess.check_output(['./voting_app', 'view_ledger'], stderr=subprocess.STDOUT)
        raw_ledger = output.decode('utf-8').strip().split('\n')
        ledger_entries = []

        for line in raw_ledger:
            parts = line.split(', ')
            entry = {}
            for part in parts:
                if ': ' in part:
                    key, value = part.split(': ', 1)
                    entry[key.strip().lower().replace(' ', '_')] = value.strip()
            if entry:
                ledger_entries.append(entry)
        print(ledger_entries)
        return render_template('view_ledger.html', ledger_entries=ledger_entries)
    except subprocess.CalledProcessError:
        return render_template('view_ledger.html', ledger_entries=None)


if __name__ == '__main__':
    app.run(debug=True)
