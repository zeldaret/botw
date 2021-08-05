use anyhow::{bail, Result};
use std::path::PathBuf;

pub fn get_repo_root() -> Result<PathBuf> {
    let current_dir = std::env::current_dir()?;
    let mut dir = current_dir.as_path();

    loop {
        if ["data", "src"].iter().all(|name| dir.join(name).is_dir()) {
            return Ok(dir.to_path_buf());
        }

        match dir.parent() {
            None => {
                bail!("failed to find repo root -- run this program inside the repo");
            }
            Some(parent) => dir = parent,
        };
    }
}

pub fn get_tools_path() -> Result<PathBuf> {
    Ok(get_repo_root()?.join("tools"))
}
