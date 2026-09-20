  ## 1. Evaluation of Your Repository Structure                                                                  
                                                                                                                 
  Your main /PORTFOLIO directory functions as an Umbrella / Container Workspace.                                 
                                                                                                                 
  ### Current Layout Breakdown:                                                                                  
                                                                                                                 
  • PORTFOLIO/ (Main Folder): Not a Git repository itself. This is correct and avoids nested repository          
  collisions.                                                                                                    
  • Independent Git Repositories (Subfolders):                                                                   
      • Patterns-in-code-and-culture/ → git@github.com:On-Off-Grid/Patterns-in-code-and-culture.git              
      • inception/ → git@github.com:On-Off-Grid/inception.git                                                    
      • CPPS/ → git@github.com:On-Off-Grid/CPPS.git                                                              
      • philosophers/ → git@github.com:On-Off-Grid/Philo_lakhar.git                                              
      • my_irc/ → git@github.com:abareich/ft_irc.git                                                             
      • minilibx-linux/ → git@github.com:42Paris/minilibx-linux.git                                              
  • Non-Git Project Folders:                                                                                     
      • cub3d/, fractol/, minishell/, minitalk/, readmes/ (Not initialized with Git yet).                        
                                                                                                                 
  ──────                                                                                                         
  ## 2. Strategies for Managing Multiple Repositories                                                            
                                                                                                                 
  ### Recommended Approach: Multi-Repo (Current Setup)                                                           
                                                                                                                 
  Keep each project as an independent Git repository inside the /PORTFOLIO parent folder.                        
                                                                                                                 
  │ Tip                                                                                  
  │ Why this approach is best for you:                                                                           
  │                                                                                                              
  │ • Each project has its own dedicated GitHub repository, issue tracker, commit history, and release tags.     
  │ • You can push to Patterns-in-code-and-culture without touching your C++ or Inception repositories.          
                                                                                                                 
  ### Quick Helper Command                                                                                       
                                                                                                                 
  To check the status of all sub-repositories at once, you can run this command from the /PORTFOLIO root:        
                                                                                                                 
    for d in */; do                                                                                              
      if [ -d "$d/.git" ]; then                                                                                  
        echo "=== 📂 Repo: $d ==="                                                                               
        git -C "$d" status -s                                                                                    
      fi                                                                                                         
    done                                                                                                         
  ──────                                                                                                         
  ## 3. End-to-End Git & Pull Request (PR) Workflow                                                              
                                                                                                                 
  A standard professional workflow consists of 6 steps:                                                          
                                                                                                                 
  │ Diagram exceeds terminal width (176 > 115 cols)                                                              
  │ Displayed as code block. Widen terminal to view inline.                                                      
                                                                                                                 
    flowchart LR                                                                                                 
        A["main branch"] -->|git checkout -b| B["feature branch"]                                                
        B -->|git commit| C["local commits"]                                                                     
        C -->|git push| D["GitHub Remote"]                                                                       
        D -->|Open PR| E["Pull Request Review"]                                                                  
        E -->|Merge PR| F["main branch updated"]                                                                 
                                                                                                                 
  ### Step 1: Create a Feature Branch                                                                            
                                                                                                                 
  Never commit directly to main when learning PR workflows. Always work in a feature branch:                     
                                                                                                                 
    # Navigate to your project directory                                                                         
    cd Patterns-in-code-and-culture                                                                              
                                                                                                                 
    # Make sure your local main is up to date                                                                    
    git checkout main                                                                                            
    git pull origin main                                                                                         
                                                                                                                 
    # Create and switch to a new feature branch                                                                  
    git checkout -b feature/static-blog-phase1                                                                   
                                                                                                                 
  ### Step 2: Stage and Commit Changes                                                                           
                                                                                                                 
    # Check modified and untracked files                                                                         
    git status                                                                                                   
                                                                                                                 
    # Stage the specific files you modified                                                                      
    git add index.html about.html pillars.html blog.html post-template.html content/who_are_we.html now.html 404.
  html                                                                                                           
                                                                                                                 
    # Create a clear commit message                                                                              
    git commit -m "feat: Add Now page, 404 page, and synchronize navigation"                                     
                                                                                                                 
  ### Step 3: Push the Branch to GitHub                                                                          
                                                                                                                 
    # Push your feature branch to GitHub and set tracking (-u)                                                   
    git push -u origin feature/static-blog-phase1                                                                
                                                                                                                 
  ### Step 4: Open and Review the Pull Request on GitHub                                                         
                                                                                                                 
  1. Open your repository on GitHub: https://github.com/On-Off-Grid/Patterns-in-code-and-culture                 
  2. You will see a banner: "feature/static-blog-phase1 had recent pushes" → Click Compare & pull request.       
  3. Fill in the PR details:                                                                                     
      • Title: feat: Add Now page and update navigation                                                          
      • Description: Highlight what changed (Phase 1 static blog integration).                                   
  4. Review your diff in the Files changed tab on GitHub:                                                        
      • Inspect line additions (green) and deletions (red).                                                      
      • Add inline comments if needed to practice reviewing code.                                                
                                                                                                                 
                                                                                                                 
  ### Step 5: Merge the Pull Request                                                                             
                                                                                                                 
  1. Click Merge pull request → Confirm merge.                                                                   
  2. Optionally click Delete branch on GitHub to keep remote branches clean.                                     
                                                                                                                 
  ### Step 6: Update Local main Branch                                                                           
                                                                                                                 
    # Switch back to main on your local machine                                                                  
    git checkout main                                                                                            
                                                                                                                 
    # Pull the newly merged main branch from GitHub                                                              
    git pull origin main                                                                                         
                                                                                                                 
    # Delete your local feature branch now that it's merged                                                      
    git branch -d feature/static-blog-phase1                                                                     
  ──────                                                                                                         
  ## 4. Hands-On Practice Exercise (Try This Now!)                                                               
                                                                                                                 
  You currently have uncommitted changes in both Patterns-in-code-and-culture and inception. You can run these   
  commands to practice creating your first PR right now:                                                         
                                                                                                                 
  ### Exercise: Push Patterns-in-code-and-culture Phase 1 via PR                                                 
                                                                                                                 
    cd /home/souhail/Desktop/Desktop/PORTFOLIO/Patterns-in-code-and-culture                                      
                                                                                                                 
    # 1. Create a new feature branch                                                                             
    git checkout -b feature/phase1-static-blog                                                                   
                                                                                                                 
    # 2. Stage all Phase 1 changes                                                                               
    git add index.html about.html pillars.html blog.html post-template.html content/who_are_we.html now.html 404.
  html                                                                                                           
                                                                                                                 
    # 3. Commit the changes                                                                                      
    git commit -m "feat(blog): implement phase 1 static blog layout and navigation"                              
                                                                                                                 
    # 4. Push to GitHub                                                                                          
    git push -u origin feature/phase1-static-blog                                                                
                                                                                                                 
  Once pushed, visit https://github.com/On-Off-Grid/Patterns-in-code-and-culture/pulls to open and review your   
  Pull Request!
