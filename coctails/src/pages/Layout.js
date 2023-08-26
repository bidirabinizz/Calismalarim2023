import { Outlet, Link } from "react-router-dom";
import "../index.css";
const Layout = () => {
  return (
    <>
      <h1 style={{ display: "inline-block" }}>Coctails</h1>
      <nav className="h1class1">
        <ul>
          <li>
            <Link to="/" className="titlekaldir">
              Home
            </Link>
          </li>
          <li>
            <Link to="/blogs" className="titlekaldir">
              Blogs
            </Link>
          </li>
          <li>
            <Link to="/contact" className="titlekaldir">
              Contact
            </Link>
          </li>
        </ul>
      </nav>

      <Outlet />
    </>
  );
};

export default Layout;
