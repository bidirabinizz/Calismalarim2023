import { Outlet, Link } from "react-router-dom";
import "./style.css";
const Layout = () => {
  return (
    <>
      <h1 className="baslik">Bahadır Bykt</h1>
      <nav>
        <ul>
          <li>
            <Link to="/">Home</Link>
          </li>
          <li>
            <Link to="/blogs">Blogs</Link>
          </li>
          <li>
            <Link to="/contact">Contact</Link>
          </li>
        </ul>
      </nav>

      <Outlet />
    </>
  );
};

export default Layout;
