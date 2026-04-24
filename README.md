# 💼 Job Portal — Full-Stack Recruitment Platform

A full-stack job portal web application built with ASP.NET and SQL Server, supporting dual-role authentication for **Employers** and **Job Seekers** with real-time messaging, interview scheduling, and application tracking.

---

## 🔐 Authentication

| Feature | Details |
|---|---|
| Login Endpoint | `/Account/Login` |
| Auth Method | Credential-based login |
| Roles Supported | `Employer`, `Job Seeker` |
| Database | SQL Server (direct credential verification) |

---

## 👤 Job Seeker Features

### 🪪 Profile Management
- ✏️ Edit personal info, career details, and upload documents/media
- 🖼️ Profile picture updates reflect **instantly** across the dashboard
- 💾 All changes are automatically persisted to the database

### 🧠 Skills
- ➕ Add / remove professional skills via the **My Skills** page
- 🔍 Skills are used as **filters** when browsing job listings
- 📊 Skills count reflected in the **Activity Overview** dashboard widget

### 💼 Browse & Save Jobs
- 🌐 Browse live job listings posted by employers
- 🔖 Save jobs for later — stored in the `SAVED_JOBS` table
- 📋 Track saved jobs from the **My Job Tracker** page

### 📨 Apply for Jobs
- 🖱️ Apply directly from a job listing page
- 📈 Application status tracked through three stages:

```
Pending  →  Interview  →  Approved
```

### 📁 My Applications Panel
- 📄 View all submitted applications with their current status
- 🗓️ See scheduled interview details (date, time, location/link, instructions)
- 💬 Chat with the employer directly from the panel

### 🔔 Notifications
- ✅ Application approval alerts
- 📅 Interview invitation notifications

---

## 🏢 Employer Features

### 🏷️ Company Profile
- 🏢 Update company information and upload company logo
- 🖼️ Logo appears on job listings and the employer dashboard

### 📝 Post a Job
- 📋 Fill in job title, description, requirements, salary, location, and type
- 🚀 Posted jobs are **immediately visible** to job seekers upon publishing

### 🗂️ Manage Jobs
- 📊 View all posted jobs with status, post date, and expiry date
- ⚡ Available actions per listing:

```
Preview  |  Edit  |  View Applicants  |  Delete
```

### 👥 Review Applications
- 📄 View all applicants for a specific job listing
- 📥 Download applicant resumes (PDF, auto-retrieved from job seeker profile)
- ⚡ Available actions per applicant:

```
Approve  |  Reject  |  Schedule Interview  |  Message
```

### 🗓️ Schedule Interviews
- 🎯 Set interview type: **Online** or **Offline**
- 📅 Specify date, time, interviewer name & email
- 🔗 Provide meeting link and instructions for the applicant
- 📲 Scheduling details are **automatically pushed** to the job seeker's application panel

### 💬 Real-Time Messaging
- ⚡ Real-time chat between job seekers and employers
- 🔁 Accessible from both sides:
  - Job Seeker → **My Applications Panel**
  - Employer → **Applicant View**

---

## 🗄️ Tech Stack

| Layer | Technology |
|---|---|
| Backend | ASP.NET (MVC / Web Forms) |
| Database | Microsoft SQL Server |
| Auth | Role-based (Employer / Job Seeker) |
| Messaging | Real-time Chat |
| File Handling | PDF Resume Upload & Download |

---

## 🚀 Getting Started

### Prerequisites
- Visual Studio 2022+
- SQL Server (LocalDB or full instance)
- .NET Framework / .NET Core (based on project target)

### Setup
```bash
# 1. Clone the repository
git clone https://github.com/your-username/your-repo-name.git

# 2. Open the solution in Visual Studio
#    File → Open → Solution (.sln)

# 3. Update the connection string in Web.config / appsettings.json
#    to point to your SQL Server instance

# 4. Run the database migration / setup script
#    (located in /Database/schema.sql or via Package Manager Console)

# 5. Build and run the project
#    Press F5 or use IIS Express
```

### Default Login
> Configure initial credentials in the database seed script or register via the signup flow.

---

## 📁 Project Structure

```
/Controllers        → MVC Controllers (Account, Job, Application, etc.)
/Models             → Data models and ViewModels
/Views              → Razor views for all pages
/Database           → SQL scripts (schema, seed data)
/wwwroot / Content  → Static assets (CSS, JS, images)
```

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).
