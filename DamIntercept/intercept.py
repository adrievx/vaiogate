import http.server
import socketserver
import threading
import urllib.parse
import tkinter as tk
from tkinter import ttk, scrolledtext
from datetime import datetime

requests_log = []

class RequestHandler(http.server.BaseHTTPRequestHandler):
    def _handle_request(self):
        parsed_url = urllib.parse.urlparse(self.path)
        content_length = int(self.headers.get('Content-Length', 0))
        body = self.rfile.read(content_length).decode('utf-8') if content_length > 0 else ""
        data = {
            "time": datetime.now().strftime("%H:%M:%S"),
            "method": self.command,
            "path": parsed_url.path,
            "query": parsed_url.query,
            "body": body,
            "headers": dict(self.headers)
        }
        requests_log.append(data)
        update_gui()
        self.send_response(200)
        self.end_headers()
        if self.command not in ("HEAD",):
            self.wfile.write(b"OK")

    def do_GET(self): self._handle_request()
    def do_POST(self): self._handle_request()
    def do_HEAD(self): self._handle_request()
    def do_PUT(self): self._handle_request()
    def do_DELETE(self): self._handle_request()
    def do_OPTIONS(self): self._handle_request()
    def do_PATCH(self): self._handle_request()

def start_server():
    with socketserver.TCPServer(("", 80), RequestHandler) as httpd:
        httpd.serve_forever()

root = tk.Tk()
root.title("Interceptor")
root.geometry("950x500")

tree = ttk.Treeview(root, columns=("time", "method", "url"), show="headings")
tree.heading("time", text="Time")
tree.heading("method", text="Method")
tree.heading("url", text="URL")
tree.column("time", width=80)
tree.column("method", width=80)
tree.column("url", width=700)
tree.pack(fill=tk.BOTH, expand=True)

details_text = scrolledtext.ScrolledText(root, wrap=tk.WORD, height=10)
details_text.pack(fill=tk.BOTH, expand=False)

def on_select(event):
    selected = tree.selection()
    if selected:
        index = int(selected[0])
        req = requests_log[index]
        details = f"Time: {req['time']}\nMethod: {req['method']}\nPath: {req['path']}\nQuery: {req['query']}\n\nHeaders:\n"
        for k, v in req['headers'].items():
            details += f"{k}: {v}\n"
        details += f"\nBody:\n{req['body']}"
        details_text.delete("1.0", tk.END)
        details_text.insert(tk.END, details)

tree.bind("<<TreeviewSelect>>", on_select)

def update_gui():
    tree.delete(*tree.get_children())
    for i, req in enumerate(requests_log):
        full_url = req['path']
        if req['query']:
            full_url += "?" + req['query']
        tree.insert("", tk.END, iid=str(i), values=(req['time'], req['method'], full_url))

threading.Thread(target=start_server, daemon=True).start()
root.mainloop()
